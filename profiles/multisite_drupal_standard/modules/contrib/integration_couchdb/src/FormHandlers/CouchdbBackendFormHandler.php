<?php

namespace Drupal\integration_couchdb\FormHandlers\Backend;

use Drupal\integration_ui\FormHandlers\Backend\AbstractBackendFormHandler;
use Drupal\integration_ui\FormHelper;

/**
 * Class CouchdbBackendFormHandler.
 *
 * @method BackendConfiguration getConfiguration(array &$form_state)
 *
 * @package Drupal\integration_ui\FormHandlers\Backend
 */
class CouchdbBackendFormHandler extends AbstractBackendFormHandler {

  /**
   * {@inheritdoc}
   */
  public function resourceSchemaForm($machine_name, array &$form, array &$form_state, $op) {
    $configuration = $this->getConfiguration($form_state);
    $form['endpoint'] = FormHelper::textField(
      t('Base endpoint'),
      $configuration->getPluginSetting("resource_schema.$machine_name.endpoint"),
      FALSE,
      t('The endpoint used for CRUD operations, e.g. /article')
    );
    $form['all_docs_endpoint'] = FormHelper::textField(
      t('List endpoint'),
      $configuration->getPluginSetting("resource_schema.$machine_name.all_docs_endpoint"),
      FALSE,
      t('The endpoint used to get all items of this resource, e.g. /articles')
    );
    $form['changes_endpoint'] = FormHelper::textField(
      t('Changes endpoint'),
      $configuration->getPluginSetting("resource_schema.$machine_name.changes_endpoint"),
      FALSE,
      t('The endpoint providing the history of changes for this resource, e.g. /changes?type=article')
    );
  }

  /**
   * {@inheritdoc}
   */
  public function form(array &$form, array &$form_state, $op) {
    $configuration = $this->getConfiguration($form_state);
    $form['base_url'] = FormHelper::textField(
      t('Base URL'),
      $configuration->getPluginSetting('backend.base_url'),
      TRUE,
      t('The base URL of the CouchDB database, e.g.: http://localhost:5984/ilayer')
    );
    $form['id_endpoint'] = FormHelper::textField(
      t('ID endpoint'),
      $configuration->getPluginSetting('backend.id_endpoint'),
      FALSE,
      t('The endpoint providing the UUID of a specified document, e.g.: /uuid')
    );
  }

  /**
   * {@inheritdoc}
   */
  public function formSubmit(array $form, array &$form_state) {

  }

  /**
   * {@inheritdoc}
   */
  public function formValidate(array $form, array &$form_state) {

  }

}
