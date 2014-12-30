<?php
/**
*inplementing my base classs base.inc that extends the migration class. 
*/
 class typeMigration extends Mybase {
  public function __construct($arguments) {

  parent::__construct($arguments);

 $this->description = t('importing announcement type  from filemaker json file to drupal');

 $fields = array(
	'type_id'=>'source_id ',
      'title' => 'title',
      'description'=>'body',
            );
    //$json_file = 'http://docroot.local:8083/sites/all/modules/fundingopportunities/data/sources/arrangement_type.json';
    
     $json_file = drupal_get_path('module', 'fundingOpportunities').'/data/sources/arrangement_type.json';
    
 $this->source = new MigrateSourceJSON($json_file , 'type_id', $fields);

 $this->destination = new MigrateDestinationNode('announcement_type');
$source_key = array(
      'type_id' => array('type' => 'int',
                      'unsigned' => TRUE,
                      'not null' => TRUE,
                      'description'=>'type_sourceID',
                     )
    );
    $this->map = new MigrateSQLMap($this->machineName, $source_key,
      MigrateDestinationNode::getKeySchema()
);

 $this->addFieldMapping('title', 'name');
  $this->addFieldMapping('body', 'description');


}

protected function createStub(Migration $migration, array $source_id) {
   $node = new stdClass();
    $node->title = t('Stub for @id', array('@id' => $source_id[0]));
  $node->body[LANGUAGE_NONE][0]['value'] = t('Stub body');
   $node->type = $this->destination->getBundle();
    $node->uid = 1;
   $node->status = 0;
   node_save($node);
    if (isset($node->nid)) {
      return array($node->nid);
    }
    else {
      return FALSE;
    }
  }
  }