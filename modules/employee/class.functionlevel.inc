<?php
/**
 * This file is part of the Achievo distribution.
 * Detailed copyright and licensing information can be found
 * in the doc/COPYRIGHT and doc/LICENSE files which should be
 * included in the distribution.
 *
 * @package achievo
 * @subpackage employee
 *
 * @copyright (c)2008 Ibuildings B.V.
 * @license http://www.achievo.org/licensing Achievo Open Source License
 *
 * @version $Revision: 5077 $
 * $Id: class.functionlevel.inc 5077 2008-06-30 20:50:48Z sandy $
 */
  useattrib("atktextattribute");
  useattrib("atknumberattribute");
/**
 * Class for managing function levels
 * @package achievo
 * @subpackage employee
 */
  class functionlevel extends atkNode
  {
    /**
     * Constructor
     */
    function functionlevel()
    {
      $this->atkNode("functionlevel");
      $this->add(new atkNumberAttribute("id",AF_AUTOKEY));
      $this->add(new atkAttribute("name",AF_OBLIGATORY|AF_SEARCHABLE, 50));
      $this->add(new atkTextAttribute("description", 0, AF_HIDE_LIST));
      $this->add(new atkNumberAttribute("id_org", AF_HIDE | AF_FORCELOAD));   

      $user = getUser();
      $this->addFilter("functionlevel.id_org = '".$user['employer_id']."'");
      $this->setTable("functionlevel","functionlevel");
      $this->setOrder("name");
    }

    /**
     * Set descriptor template
     *
     * @return string
     */
    function descriptor_def()
    {
      return "[name]";
    }

    function initial_values(){
      $user = getUser();
      $id_org = $user['employer_id'];

      return array("id_org" => $id_org);
    }
  }

?>