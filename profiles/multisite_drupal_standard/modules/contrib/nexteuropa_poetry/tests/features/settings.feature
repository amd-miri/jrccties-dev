@api
Feature: Settings

  Scenario: Users with "configure poetry client" permissions can configure Poetry client.

    Given I am logged in as a user with the "configure poetry client, access administration pages" permission
    And I visit "admin/config"

    Then I should see the link "Poetry client"
    When I click "Poetry client"
    And I fill in the following:
      | edit-nexteuropa-poetry-notification-username | notification-username |
      | edit-nexteuropa-poetry-notification-password | notification-password |
      | edit-nexteuropa-poetry-service-username      | service-username      |
      | edit-nexteuropa-poetry-service-password      | service-password      |
      | edit-nexteuropa-poetry-service-wsdl          | service-wsdl          |
    And I press "Save configuration"
    Then the "edit-nexteuropa-poetry-notification-username" field should contain "notification-username"
    And the "edit-nexteuropa-poetry-notification-password" field should contain "notification-password"
    And the "edit-nexteuropa-poetry-service-username" field should contain "service-username"
    And the "edit-nexteuropa-poetry-service-password" field should contain "service-password"
    And the "edit-nexteuropa-poetry-service-wsdl" field should contain "service-wsdl"
