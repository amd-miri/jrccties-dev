<?php

namespace Drupal\Tests\nexteuropa_poetry\Behat;

use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Gherkin\Node\PyStringNode;
use EC\Behat\PoetryExtension\Context\RawPoetryContext;

/**
 * Class PoetryContext.
 *
 * @package Drupal\nexteuropa_poetry\Tests\Behat
 */
class PoetryContext extends RawPoetryContext {

  /**
   * Poetry context.
   *
   * @var \EC\Behat\PoetryExtension\Context\PoetryContext
   */
  private $poetryContext;

  /**
   * Gather contexts.
   *
   * @param \Behat\Behat\Hook\Scope\BeforeScenarioScope $scope
   *   Context scope.
   *
   * @BeforeScenario
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();
    $this->poetryContext = $environment->getContext('EC\Behat\PoetryExtension\Context\PoetryContext');
    $this->poetryContext->setPoetry(nexteuropa_poetry_client());
  }

  /**
   * Send message to mock service.
   *
   * @param string $name
   *   Message name.
   * @param \Behat\Gherkin\Node\PyStringNode $string
   *   Message values as YAML.
   *
   * @When the site sends the following :name message to Poetry:
   */
  public function sendMessage($name, PyStringNode $string) {
    $poetry = nexteuropa_poetry_client();
    $wsdl = $this->poetryMock->getServiceUrl('/wsdl');
    $poetry->getSettings()->set('service.wsdl', $wsdl);
    $message = $poetry->get($name)->withArray($this->parse($string));
    $this->response = $poetry->getClient()->send($message);
  }

}
