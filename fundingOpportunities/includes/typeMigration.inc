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
    $json_file = 'http://docroot.local:8083/sites/all/modules/fundingopportunities/data/sources/arrangement_type.json';
    //$mjason = file_get_contents('data/sources/funding_jsonlintverified.json');
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
}