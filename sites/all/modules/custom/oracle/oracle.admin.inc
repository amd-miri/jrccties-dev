<?php

// $Id

function oracle_admin_settings()
{
  global $oracle_debug, $oracle_use_memcached, $oracle_cache_blobs;
  
  $form['oracle-options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Oracle driver options'),
    '#description' => t('This settings are used to configure the oracle driver for this site.'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['oracle-options']['debug'] = array(
   '#type' => 'checkbox',
   '#title' => t('Debug?'),
   '#description' => t("output SQL statements with syslog (in the http server error log). To enable this option set \$"."GLOBALS['oracle_debug']= true; in your settings.php"),
   '#default_value' => ($oracle_debug ? '1' : '0')
  );
  
  $form['oracle-options']['cache'] = array(
   '#type' => 'checkbox',
   '#title' => t('Can we use cache_set / cache_get for statements ?'),
   '#description' => t("You can enable to gain performance improvements. <strong>Don't use it unless you have memcached or cacherouter module active (cache_oracle table should be addressed to a memory engine for cacherouter)</strong>. To enable this option set \$"."GLOBALS['oracle_use_memcached']= true; in your settings.php"),
   '#default_value' => ($oracle_use_memcached ? '1' : '0')
  );

  $form['oracle-options']['cacheb'] = array(
   '#type' => 'checkbox',
   '#title' => t('Can we use cache_set / cache_get for blobs ?'),
   '#description' => t("You can enable to gain performance improvements. <strong>Don't use it unless you have memcached or cacherouter module active (cache_oracle_blobs table should be addressed to the file engine for cacherouter)</strong>. To enable this option set \$"."GLOBALS['oracle_cache_blobs']= true; in your settings.php"),
   '#default_value' => ($oracle_cache_blobs ? '1' : '0')
  );

  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Save configuration'),
  );
  $form['reset'] = array(
    '#type'  => 'submit',
    '#value' => t('Reset to defaults'),
  );
  return $form;
}

function oracle_admin_settings_submit($form, &$form_state) {
  $op = $form_state['clicked_button']['#value'];
  switch ($op) {
    case "Save configuration":
      $values = $form_state['values'];

      drupal_set_message(t('The configuration options have been saved.'));
      
      break;
    case "Reset to defaults":

      drupal_set_message(t('The configuration options have been reset to their default values.'));
      break;
  }

}

function oracle_admin_performance()
{
  global $oracle_user;
  
  $conn= Database::getConnection();
  
  try
  {
	  $rows = array();
	  $result = $conn->oracleQuery('select * 
	                            from 
	                            (       select sql_id,
	                                           sql_text, 
	                                           cpu_time, 
	                                           elapsed_time, 
	                                           user_io_wait_time,
	                                           executions
	                                      from v$sqlarea 
	                                     where parsing_schema_name= ? 
	                                       and module like \'httpd%\' 
	                                       and sql_text not like \'%v$sqlarea%\'
	                                    order by '.(isset($_GET['order']) ? $_GET['order'] : 'elapsed_time').' desc
	                            ) where rownum < 11',array($oracle_user));

      foreach ($result as $row) 
      {
	    $rows[] = array(
	      l($row['sql_text'], 'admin/config/development/oracle/performance/sql/'. $row['sql_id']),
	      $row['cpu_time'],
	      $row['elapsed_time'],
	      $row['user_io_wait_time'],
	      $row['executions']
	    );
	  }
      
	  $header = array(
	    t('SQL Text'),
	    '<a href="?order=cpu_time">'.t('Total CPU time (in microseconds)').'</a>',
	    '<a href="?order=elapsed_time">'.t('Total elapsed time (in microseconds)').'</a>',
	    '<a href="?order=user_io_wait_time">'.t('Total user I/O wait time (in microseconds)').'</a>',
	    '<a href="?order=executions">'.t('Total executions').'</a>'
	  );
	
	  $output= '<h2>Top 10 statements by elapsed time for user '.$oracle_user.'</h2>'; 
	  $output.= theme('table',array( 'header' => $header, 'rows' => $rows));
	  return $output;
   }
   catch (Exception $ex)
   {
       return 'missing: grant select on v_$sqlarea to '.$oracle_user;
   }
}

function oracle_indent_plan($spaces)
{
    $retval="";
    
    while ($spaces-->0)
     $retval.= '&nbsp;';
     
    return $retval;
}

function oracle_admin_performance_sql($sql_id) 
{
  global $oracle_user;
  
  $conn= Database::getConnection();

  
  try
  {
  
	  $output= '<h2>SQL id: '.$sql_id.'</h2><a href="'.base_path().'admin/config/development/oracle/performance">back to performance</a>'; 
	
	  $arr = $conn->oracleQuery('select * 
	                            from v$sqlarea 
	                           where sql_id= ?',array($sql_id))->fetch();
	
	  $output.= '<p>'.$arr['sql_fulltext'].'</p>'; 
	
	  $output.= '<h3>Current execution plan</h3>'; 
	
	  $rows = array();
	  $result = $conn->oracleQuery('select level, tab.*
	                            from 
	                            (
	                                select operation, 
	                                       options, 
	                                       object_name,
	                                       cpu_cost,
	                                       io_cost,
	                                       cost,
	                                       time,
	                                       temp_space,
	                                       id,
	                                       parent_id
	                                  from v$sql_plan 
	                                 where sql_id= ?
	                                   and child_number= 0
	                            ) tab
	                            start with parent_id  is null
	                            connect by prior id= parent_id',array($sql_id));
	
      foreach ($result as $row) 
	    $rows[] = array(
	      oracle_indent_plan($row['level']).$row['operation'],
	      $row['options'],
	      $row['object_name'],
	      $row['cpu_cost'],
	      $row['io_cost'],
	      $row['cost'],
	      $row['time'],
	      $row['temp_space']
	    );
	  
	
	  $header = array(
	    t('Operation'),
	    t('Options'),
	    t('Object name'),
	    t('CPU cost'),
	    t('I/O cost'),
	    t('Elapsed time'),
	    t('Temp space')
	  );
	
	  $output.= theme('table',array( 'header' => $header, 'rows' => $rows));
	  
	  
	  $rows = array();

	  foreach ($arr as $key => $value)
	   if ($key!='sql_fulltext'&&$key!='sql_text'&&$key!='optimizer_env'&&$key!='bind_data')
	   $rows[]= array($key,$value);
	
	  $header = array(
	    t('Column'),
	    t('Value')
	  );
	
	  $output.= '<h3>v$sqlarea</h3>'; 
	  $output.= theme('table',array( 'header' => $header, 'rows' => $rows));
	  return $output;
	  
   }
   catch (Exception $ex)
   {
       return 'missing: grant select on v_$sql_plan  to '.$oracle_user.';';
   }
	  
}



function oracle_admin_translate($form, &$form_state)
{
  $values = isset($form_state['values']) ? $form_state['values'] : array();
  
  $conn= Database::getConnection();

  $form['oracle-translate'] = array(
    '#type' => 'fieldset',
    '#title' => t('Oracle statement translation tool'),
    '#description' => t('You can use this form to translate a Drupal/MySQL statement to its Oracle version'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['oracle-translate']['drupal'] = array(
   '#type' => 'textarea',
   '#title' => t('Drupal statement'),
   '#description' => t("Use this field to input the SQL to translate"),
   '#default_value' => (isset($values['drupal']) ? $values['drupal'] : 'SELECT * FROM {node}')
  );

  $form['oracle-translate']['oracle'] = array(
   '#type' => 'textarea',
   '#title' => t('Oracle translation'),
   '#description' => t("Get the Oracle translation from here"),
   '#value' => $conn->prepareQuery(isset($values['drupal']) ? $values['drupal'] : 'SELECT * FROM {node}')->queryString,
   '#attributes' => array('readonly' => 'readonly')
  );

  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Translate'),
  );
  
  return $form;
}

function oracle_admin_translate_submit($form, &$form_state)
{
  $op = $form_state['clicked_button']['#value'];
  switch ($op) {
    case t("Translate"):
      $values = $form_state['values'];

      drupal_set_message(t('Statement translated.'));
      $form_state['rebuild'] = TRUE;
      break;
  }
}


function oracle_admin_longid()
{
  $conn= Database::getConnection();

  $rows = array();
  $result = $conn->oracleQuery('select identifier, \''.ORACLE_LONG_IDENTIFIER_PREFIX.'\'||id translation, id from long_identifiers order by length(identifier) desc');
  
  foreach ($result as $row) 
    $rows[] = array(
      $row['identifier'],
      $row['translation']
    );
  

  $header = array(
    t('Identifier'),
    t('Translation')
  );

  $output= '<h2>Long identifiers</h2>'; 
  $output.= '<p>Those are the identifiers that have been translated to fit the Oracle identifier maximum length of '.ORACLE_IDENTIFIER_MAX_LENGTH.' characters. The LONG_IDENTIFIERS table is managed automatically by the driver. You should delete obsolete records.</p>'; 
  $output.= theme('table',array( 'header' => $header, 'rows' => $rows));
  return $output;
}

function oracle_admin_blob()
{
    $conn= Database::getConnection();

    $blob_count= $conn->oracleQuery('select count(*) from blobs')->fetchColumn();
    $job= db_query("select job id, interval, to_char(next_date,'DD/MM/YYYY') next_date, to_char(last_date,'DD/MM/YYYY') last_date from user_jobs where lower(what) like ?",array('%blobs_cleaner.cleanup%'))->fetchObject();
    
  $form['oracle-blob-options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Oracle BLOBS table'),
    '#description' => t('This settings are used to manage the cleanup of BLOBS table.'
                        .'<p>You actually have <b>'.$blob_count.'</b> blobs. Those blobs are created automatically by the Oracle driver when some value exceed the maximum varchar2 length ('.ORACLE_MAX_VARCHAR2_LENGTH.' char), you should schedule a database job to cleanup the unused values.</p>'
                        .($job&&$job->last_date ? '<p>The cleanup job ('.$job->id.') was executed last time on '.$job->last_date : '') ),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['oracle-blob-options']['next_date'] = array(
   '#type' => 'textfield',
   '#title' => t('Next date'),
   '#description' => t("The next date when BLOBS table will be cleaned up"),
   '#default_value' => ($job ? $job->next_date : date('d/m/Y'))
  );
  
  $form['oracle-blob-options']['interval'] = array(
   '#type' => 'textfield',
   '#title' => t('Interval'),
   '#description' => t("Schedule the job every day (SYSDATE+1) or hour (SYSDATE+1/24) etc..."),
   '#default_value' => ($job ? $job->interval : 'SYSDATE+1')
  );

  $form['oracle-blob-options']['prefixes'] = array(
   '#type' => 'textfield',
   '#title' => t('DB Prefixes'),
   '#description' => t("Check if this db_prefixes use BLOB values in the BLOBS table (a comma separated list of db_prefixes)"),
   '#default_value' => variable_get('oracle_blob_cleanup_prefixes','')
  );


  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Schedule'),
  );
  return $form;
}


function oracle_admin_blob_submit($form, &$form_state) {
      $values = $form_state['values'];

      $db_prefixes= "";
      
      
      if (trim($values['prefixes'])!='')
      {
         $prefs= explode(',',$values['prefixes']);
         $db_prefixes= "(vargs(user";   
         
         foreach ($prefs as $pref)
           $db_prefixes.= ",'".str_replace("'","''",(strtoupper(trim($pref))))."'";
           
         $db_prefixes.= "))";     
      }
      
      variable_set('oracle_blob_cleanup_prefixes',trim($values['prefixes']));
      
      db_query("declare
                   jobid binary_integer;
                begin
                
                   begin
                    select job
                      into jobid
                      from user_jobs
                     where what like ?;
                    
                    dbms_job.remove(jobid);
                   exception
                     when no_data_found then
                       null;
                   end;
                   
                    dbms_job.submit(job => jobid, 
                                    what => 'blobs_cleaner.cleanup".$db_prefixes.";',
                                    next_date => to_date(?,'DD/MM/YYYY'),
                                    interval => ?);
                    
                    commit;
                
                end;",array('%blobs_cleaner.cleanup%',
                            $values['next_date'],
                            $values['interval']));

      drupal_set_message(t('The BLOBS cleanup job have been scheduled.'));      
}


function oracle_admin_drcp()
{
    $output= '<h2>Database Resident Connection Pool</h2>'; 
    $output.= '<p>Not yet implemented. We would like to expose an interface to configure the <a href="http://www.oracle.com/technology/tech/oci/pdf/oracledrcp11g.pdf">DRCP</a> from drupal.</p>'; 
    return $output;
}
