@api @poetry @watchdog
Feature: Requests

  Scenario: Test request.

    Given I change the variable "nexteuropa_poetry_notification_username" to "foo"
    And I change the variable "nexteuropa_poetry_notification_password" to "bar"
    And I change the variable "nexteuropa_poetry_service_username" to "foo"
    And I change the variable "nexteuropa_poetry_service_password" to "bar"

    Given Poetry will return the following XML response:
    """
    <?xml version="1.0" encoding="utf-8"?><POETRY xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://intragate.ec.europa.eu/DGT/poetry_services/poetry.xsd">
        <request communication="synchrone" id="WEB/2017/40029/0/0/TRA" type="status">
            <demandeId>
                <codeDemandeur>WEB</codeDemandeur>
                <annee>2017</annee>
                <numero>40029</numero>
                <version>0</version>
                <partie>0</partie>
                <produit>TRA</produit>
            </demandeId>
            <status type="request" code="0">
                <statusDate>06/10/2017</statusDate>
                <statusTime>02:41:53</statusTime>
                <statusMessage>OK</statusMessage>
            </status>
        </request>
    </POETRY>
    """

    When the site sends the following "request.create_translation_request" message to Poetry:
    """
      identifier:
        code: STSI
        year: 2017
        number: 40017
        version: 0
        part: 11
        product: REV
      details:
        client_id: 'Job ID 3999'
        title: 'NE-CMS: Erasmus+ - Erasmus Mundus Joint Master Degrees'
        author: 'IE/CE/EAC'
        responsible: 'EAC'
        requester: 'IE/CE/EAC/C/4'
        applicationId: 'FPFIS'
        delay: '12/09/2017'
        reference_files_remark: 'https://ec.europa.eu/programmes/erasmus-plus/opportunities-for-individuals/staff-teaching/erasmus-mundus_en'
        procedure: 'NEANT'
        destination: 'PUBLIC'
        type: 'INTER'
    """

    And Poetry service received request should contain the following XML portion:
    """
      <retour type="webService" action="UPDATE">
        <retourUser><![CDATA[notification-username]]></retourUser>
        <retourPassword><![CDATA[notification-password]]></retourPassword>
        <retourAddress><![CDATA[!poetry.client.wsdl]]></retourAddress>
        <retourPath><![CDATA[handle]]></retourPath>
      </retour>
    """
