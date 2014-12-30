<?php
/**
*inplementing my base classs base.inc that extends the migration class. 
*/
 class sponsorsMigration extends Mybase {
  public function __construct($arguments) {

  parent::__construct($arguments);

 $this->description = t('importing Sponsors from filemaker json file to drupal');

 $fields = array(
		'sponsor_id' =>'source ID',
      'name' => 'Name',
      'description'=>'body',
            );
    $json_file = 'http://docroot.local:8083/sites/all/modules/fundingopportunities/data/sources/sponsor.json';
    //$mjason = file_get_contents('data/sources/funding_jsonlintverified.json');
 $this->source = new MigrateSourceJSON($json_file , 'sponsor_id' , $fields);

 $this->destination = new MigrateDestinationNode('sponsor');
$source_key = array(
      'sponsor_id' => array('type' => 'int',
                      'unsigned' => TRUE,
                      'not null' => TRUE,
                      'description'=>'sponsor_sourceID',
                     )
    );
    $this->map = new MigrateSQLMap($this->machineName, $source_key,
      MigrateDestinationNode::getKeySchema()
);

 $this->addFieldMapping('title', 'name');
  $this->addFieldMapping('body', 'description');


}
}

