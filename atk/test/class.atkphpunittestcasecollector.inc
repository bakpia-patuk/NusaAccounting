<?php

  /**
   * This file is part of the Achievo ATK distribution.
   * Detailed copyright and licensing information can be found
   * in the doc/COPYRIGHT and doc/LICENSE files which should be
   * included in the distribution.
   *
   * @package atk
   * @subpackage test
   *
   * @copyright (c)2006 Ibuildings.nl BV
   * @license http://www.achievo.org/atk/licensing ATK Open Source License
   *
   * @version $Revision: 5149 $
   * $Id: class.atkphpunittestcasecollector.inc 6354 2009-04-15 02:41:21Z mvdam $
   */
  atkimport("atk.test.atktestcasecollector");

  /**
   * Collector of PHPUnit testcases
   *
   * @author Boy Baukema <boy@achievo.org>
   * @package atk
   * @subpackage test
   */
  class atkPHPUnitTestCaseCollector extends atkTestCaseCollector
  {
    function isValidTestClass($fullpath, $filename, $testclassname)
    {
      if (parent::isValidTestClass($fullpath,$filename,$testclassname) &&
          strstr($filename,'phpunit')) return true;
      return false;
    }

    function addTestClass($fullpath, $testclassname)
    {
      $this->m_tester->addTestFile($fullpath);
    }
  }

?>