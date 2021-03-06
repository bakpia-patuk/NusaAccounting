<?php

  /**
   * This file is part of the Achievo ATK distribution.
   * Detailed copyright and licensing information can be found
   * in the doc/COPYRIGHT and doc/LICENSE files which should be
   * included in the distribution.
   *
   * @package atk
   * @subpackage attribute
   * @access private
   *
   * @copyright (c)2007 Ibuildings
   * @license http://www.achievo.org/atk/licensing ATK Open Source License
   *
   * $Id: class.test_atknumberattribute.inc 6548 2009-10-29 08:29:47Z peter $
   * @author Yury Golovnya  <ygolovnya@achievo.org>
   * @version $Revision: 5997 $
   */


  /**
   * @internal includes
   */
  atkimport("atk.attributes.atknumberattribute");

  /**
   * Testcases for class atkNumberAttribute
   *
   * @author Yury Golovnya <ygolovnya@achievo.org>
   * @package atk
   * @subpackage attribute
   * @access private
   */
  class test_atknumberattribute extends atkAttributeTestCase
  {
    private $attr;
    
    /**
     * Setup the testcase.
     */
    function setup()
    {
      $this->attr = new atkNumberAttribute("name",0,10,2);
    }

    /**
     * Test method.
     */
    function test_attribute()
    {           
      $this->apiTest(new atknumberattribute(("name")));
    }              

    function test_getSearchCondition()
    {
      $db = &atkGetDb();
      $query = &$db->createQuery();
      
      $attribute = &new atkNumberAttribute("name");
      $value = 1;
      
      $searchString = $attribute->getSearchCondition($query,"table",$value,"substring");
      $etalonString = "UPPER(table.name) LIKE UPPER('%1%')";
      $this->assertEqual($searchString, $etalonString,"Search number 1 - %s");

      $value = 0;
      
      $searchString = $attribute->getSearchCondition($query,"table",$value,"substring");
      $etalonString = "UPPER(table.name) LIKE UPPER('%0%')";
      $this->assertEqual($searchString, $etalonString,"Search number 0 - %s");

      $value = "0";
      
      $searchString = $attribute->getSearchCondition($query,"table",$value,"substring");
      $etalonString = "UPPER(table.name) LIKE UPPER('%0%')";
      $this->assertEqual($searchString, $etalonString,"Search string '0' - %s");

      $value = "1";
      
      $searchString = $attribute->getSearchCondition($query,"table",$value,"substring");
      $etalonString = "UPPER(table.name) LIKE UPPER('%1%')";
      $this->assertEqual($searchString, $etalonString,"Search string '1' - %s");
    }
    
    function test_removeSeparators_no_seperator()
    {
      $this->assertEqual(2000,$this->attr->removeSeparators(2000,','));
      $this->assertEqual(2000,$this->attr->removeSeparators(2000,'.'));
      $this->assertEqual(2000,$this->attr->removeSeparators(2000,','));
    }
    
    function test_removeSeparators_decimal()
    {
      $output = 200.23;
      
      $this->assertEqual($output,$this->attr->removeSeparators('200,23',','));
      $this->assertEqual($output,$this->attr->removeSeparators('200.23','.'));
      $this->assertEqual($output,$this->attr->removeSeparators('200,23',','));
    }
    
    function test_removeSeparators_thousand()
    {
      $output = 2000.23;
      
      $this->assertEqual($output,$this->attr->removeSeparators('2000,23',',','.'));
      $this->assertEqual($output,$this->attr->removeSeparators('2.000,23',',','.'));
      $this->assertEqual($output,$this->attr->removeSeparators('2 000,23',',',' '));
      $this->assertEqual($output,$this->attr->removeSeparators('2,000.23','.',','));        
      
      $this->assertEqual('200093202.23',$this->attr->removeSeparators('2.000.93202,23',',','.'));
    }
    
    function test_removeSeparators_invalid_settings()
    {
      // test invalid settings
      // all invalid output will be catched by the validate function
      $this->assertEqual('2000.23',$this->attr->removeSeparators('2.000,23',',',','));
      $this->assertEqual('2.00023',$this->attr->removeSeparators('2.000,23','.',','));
      $this->assertEqual('2.000,23',$this->attr->removeSeparators('2.000,23',' ',' '));
    }
    
    function test_removeSeparators_invalidinput()
    {
      // test invalid input
      // all invalid output will be catched by the validate function
      $this->assertEqual('dummy',$this->attr->removeSeparators('dummy',',',','));
      $this->assertEqual('23434343',$this->attr->removeSeparators('23.4343.43',',','.'));
      $this->assertEqual('23-4343-43',$this->attr->removeSeparators('23-4343-43',',','.'));
    }
    
    function test_UseThousandsSeparator()
    {
      $this->assertFalse($this->attr->getUseThousandsSeparator());
      $this->attr->setUseThousandsSeparator(true);
      $this->assertTrue($this->attr->getUseThousandsSeparator());
    }
    
    function test_attr_display_bogus()
    {
      $this->assertTrue(($this->attr->display(array('bogus_field' => '200'))) === '');
    }
    function test_attr_display()
    {
      $this->assertEqual('200,00',$this->attr->display(array('name' => '200')));
      $this->assertEqual('2000,00',$this->attr->display(array('name' => '2000')));
      $this->assertEqual('2000,83',$this->attr->display(array('name' => '2000.832892389')));
      $this->assertEqual('2123000,83',$this->attr->display(array('name' => '2123000.832892389')));
      
      $this->attr->setUseThousandsSeparator(true);
      $this->assertEqual('2.000,00',$this->attr->display(array('name' => '2000')));
      $this->assertEqual('2.000,83',$this->attr->display(array('name' => '2000.832892389')));
      $this->assertEqual('2.123.000,83',$this->attr->display(array('name' => '2123000.832892389')));
    }
    
    function test_decimal_seperator()
    {
      $this->attr->setDecimalSeparator('.');
      $this->assertTrue($this->attr->getDecimalSeparator());
    }
    
    function test_thousands_seperator()
    {
      $this->attr->setThousandsSeparator('.');
      $this->assertTrue($this->attr->getThousandsSeparator());
    }
    
    function test_decimals()
    {
      $attr = new atkNumberAttribute("name",0,10,0);
      $attr->setUseThousandsSeparator(true);      
      $this->assertEqual('200', $attr->display(array('name' => '200')));
      $this->assertEqual('2.001', $attr->display(array('name' => '2000.832892389')));
      $this->assertEqual('2.123.001', $attr->display(array('name' => '2123000.832892389')));
      
      $attr = new atkNumberAttribute("name",0,10,2);
      $attr->setUseThousandsSeparator(true);      
      $this->assertEqual('200,00', $attr->display(array('name' => '200')));
      $this->assertEqual('2.000,83', $attr->display(array('name' => '2000.832892389')));
      $this->assertEqual('2.123.000,83', $attr->display(array('name' => '2123000.832892389')));
      
      $attr = new atkNumberAttribute("name",0,10,3);
      $attr->setUseThousandsSeparator(true);      
      $this->assertEqual('200,000', $attr->display(array('name' => '200')));
      $this->assertEqual('2.000,833', $attr->display(array('name' => '2000.832892389')));
      $this->assertEqual('2.123.000,833', $attr->display(array('name' => '2123000.832892389')));
      
      $attr = new atkNumberAttribute("name",0,10,5);
      $attr->setUseThousandsSeparator(true);
      $this->assertEqual('200,00000', $attr->display(array('name' => '200')));
      $this->assertEqual('2.000,83289', $attr->display(array('name' => '2000.832892389')));
      $this->assertEqual('2.123.000,83289', $attr->display(array('name' => '2123000.832892389')));
      
      $attr = new atkNumberAttribute("name",0,10,7);
      $attr->setUseThousandsSeparator(true);
      $this->assertEqual('200,0000000', $attr->display(array('name' => '200')));
      $this->assertEqual('2.000,8328924', $attr->display(array('name' => '2000.832892389')));
      $this->assertEqual('2.123.000,8328900', $attr->display(array('name' => '2123000.832892389')));
    }
    
    function test_metdata()
    {
      // metadata specifies 3 decimals      
      $metadata = array('name' => array('gentype' => 'decimal', 'len' => '8,3'));
      $attr = new atkNumberAttribute("name");
      $attr->fetchMeta($metadata);      
      $attr->setUseThousandsSeparator(true);      
      $this->assertEqual('200,000', $attr->display(array('name' => '200')));
      $this->assertEqual('2.000,833', $attr->display(array('name' => '2000.832892389')));
      $this->assertEqual('2.123.000,833', $attr->display(array('name' => '2123000.832892389')));      
      
      // metadata specifies 5 decimals
      $metadata = array('name' => array('gentype' => 'decimal', 'len' => '8,5'));
      $attr = new atkNumberAttribute("name");
      $attr->fetchMeta($metadata);
      $attr->setUseThousandsSeparator(true);
      $this->assertEqual('200,00000', $attr->display(array('name' => '200')));
      $this->assertEqual('2.000,83289', $attr->display(array('name' => '2000.832892389')));

      // metadata specifies more decimals than we specify in the attribute, use the lowest value      
      $metadata = array('name' => array('gentype' => 'decimal', 'len' => '8,3'));
      $attr = new atkNumberAttribute("name", 0, 10, 2);
      $attr->fetchMeta($metadata);      
      $attr->setUseThousandsSeparator(true);      
      $this->assertEqual('200,00', $attr->display(array('name' => '200')));
      $this->assertEqual('2.000,83', $attr->display(array('name' => '2000.832892389')));
      $this->assertEqual('2.123.000,83', $attr->display(array('name' => '2123000.832892389')));      
      
      // metadata specifies less decimals than we specify in the attribute, use the lowest value
      $metadata = array('name' => array('gentype' => 'decimal', 'len' => '8,4'));
      $attr = new atkNumberAttribute("name", 0, 10, 6);
      $attr->fetchMeta($metadata);
      $attr->setUseThousandsSeparator(true);
      $this->assertEqual('200,0000', $attr->display(array('name' => '200')));
      $this->assertEqual('2.000,8329', $attr->display(array('name' => '2000.832892389')));
      
      // no metadata given, use the default decimals which is null and will be threated as 0
      $attr = new atkNumberAttribute("name");
      $attr->setUseThousandsSeparator(true);      
      $this->assertEqual('200', $attr->display(array('name' => '200')));
      $this->assertEqual('2.001', $attr->display(array('name' => '2000.832892389')));
      $this->assertEqual('2.123.001', $attr->display(array('name' => '2123000.832892389')));            
    }
  }
?>