<?php
/**
*inplementing my base classs base.inc that extends the migration class. 
*/
 class opportunities extends Mybase {
  public function __construct($arguments) {
 
  parent::__construct($arguments);
  
 $this->description = t('importing funding opportunities from filemaker json file to drupal');

 $fields = array(
     'pgid'=>'source funding_id',
      'title' => 'title',
      'number' => 'number',
	'url'=>'url',
	'source_sponsor_ID'=>'Sponsor',
	'source_program_ID'=>'Program',
	'type_id'=>'Type',
      'preproposal_deadline' => 'preproposal_deadline',
	'proposal_deadline'=>'proposal_deadline',
	'source_RADS_ID'=>'RADS',
    );
    
    //$mjason = "/Users/indiaye/bkup_oct_17_14/hjf/docroot/sites/all/modules/fundingOpportunities/data/sources/latestjason.json";
    $mjason=drupal_get_path('module', 'fundingOpportunities').'/data/sources/latestjason.json';
 $this->source = new MigrateSourceJSON( $mjason, 'pgid', $fields);

 $this->destination = new MigrateDestinationNode('funding_opportunity');


$source_key = array(
      'pgid' => array('type' => 'int',
                      'unsigned' => TRUE,
                      'not null' => TRUE,
		      'description'=>'funding_opportunitiy_sourceID',
                     )
    );
    $this->map = new MigrateSQLMap($this->machineName, $source_key,
      MigrateDestinationNode::getKeySchema()
);
$this->addFieldMapping('title', 'title');
$this->addFieldMapping('field_opportunity_number', 'number');
$this->addFieldMapping('field_related_url', 'url');
 $this->addFieldMapping('field_relate_sponsor', 'source_sponsor_ID')
 		->sourceMigration('sponsorMigration');
 		
 $this->addFieldMapping('field_related_program', 'source_program_ID')
 	->sourceMigration('programMigration')
 	->separator(',');
 
 $this->addFieldMapping('field_related_announcement_type', 'type_id')
 	->sourceMigration('typeMigration');
 	
 $this->addFieldMapping('field_prepropsal_loideadline_dat', 'preproposal_deadline');
 $this->addFieldMapping('field_proposal_deadline', 'proposal_deadline');
 $this->addFieldMapping('field_rads', 'source_RADS_ID')
 		->sourceMigration('radsMigration');
 			//->separator(',');





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
function mylookup(){
$type= 'RADS';
$status= 1;
$result = db_query("SELECT nid,created FROM {node} Where type=:type and status =:status and title=:title ",

array(':type'=>$type, ':status' =>1,':title'=>'source_RADS_ID',));

// Result is returned as a iterable object that returns a stdClass object on each iteration
//if(!empty($result)){

foreach ($result as $record) {
  // Perform operations on $record->title, etc. here.
  
//echo $record->title."<br/>";
return $record->nid."<br/>";
//return $result;
}

}
}


