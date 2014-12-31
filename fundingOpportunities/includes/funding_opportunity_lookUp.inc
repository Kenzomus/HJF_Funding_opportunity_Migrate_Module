<?php
/**
*inplementing my base classs base.inc that extends the migration class. 
*/
 class funding_opportunity_lookUp extends Mybase {
  public function __construct($arguments) {
 
  parent::__construct($arguments);
  
 $this->description = t('importing funding opportunities from filemaker json file to drupal');
// $this->dependencies=('radsMigration');
 $fields = array(
     'pgid'=>'source funding_id',
      'title' => 'title',
      'number' => 'number',
	'url'=>'url',
	'source_sponsor_ID'=>'Sponsor',
	'source_program_ID'=>'Program',
	'source_type_ID'=>'Type',
      'preproposal_deadline' => 'preproposal_deadline',
	'proposal_deadline'=>'proposal_deadline',
	'source_RADS_ID'=>'RADS',
  
  );
    
    
    //$mjason = "/Users/indiaye/bkup_oct_17_14/hjf/docroot/sites/all/modules/fundingOpportunities/data/sources/funding_opportunity_look_up";
   
    $mjason=drupal_get_path('module', 'fundingOpportunities').'/data/sources/funding_opportunity_look_up';
    
    //"/Users/indiaye/bkup_oct_17_14/hjf/docroot/sites/all/modules/fundingOpportunities/data/sources/latestjason.json";
    //$mjason='public://feeds/funding_jsonlintverified_6.json';
 $this->source = new MigrateSourceJSON( $mjason, 'number', $fields);

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
 				->sourceMigration('sponsorMigration')
 				;
 $this->addFieldMapping('field_related_program', 'source_program_ID')
 			->separator(',')
 			->sourceMigration('programMigration');
 $this->addFieldMapping('field_related_announcement_type', 'source_type_ID')
 						->sourceMigration('typeMigration');
 $this->addFieldMapping('field_prepropsal_loideadline_dat', 'preproposal_deadline');
 $this->addFieldMapping('field_proposal_deadline', 'proposal_deadline');
 $this->addFieldMapping('field_rads', 'source_RADS_ID')
 						//->callbacks'(mylookup(source_RADS_ID)')
 							//->sourceMigration('radsMigration')
 								->separator(',');
 			  		//->callbacks(array($this, 'mylookup'));




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
  
  
// create a function that take the nodetype as an argument and the title to return the node id 
function mylookup($node_type,$title){
//$title= "Combat Casualty Care ";
//$type= 'RADS';
$status= 1;
$result = db_query("SELECT nid, title FROM {node} Where type=:type and status =:status && title=:title ",

array(':type'=>$type, ':status' =>1,'title'=>$title));

// Result is returned as a iterable object that returns a stdClass object on each iteration
//if(!empty($result)){

foreach ($result as $record) {
  // Perform operations on $record->title, etc. here.
  
//echo $record->title."<br/>";
//echo "the id for the record ID is :".$record->nid;
//." ".$record->title."<br/>";

}
return $record->nid;

//return  "cannot retrieve data from the db";
 }
 



function prepareRow($row){

$title= $row->source_RADS_ID;
$row->source_RADS_ID = $this->mylookup('Rads',$title);


$title= $row->source_sponsor_ID;
$row->source_sponsor_ID = $this->mylookup('sponsor',$title);

$title= $row->source_program_ID;
$row->source_program_ID = $this->mylookup('program',$title);


$title= $row->source_type_ID;
$row->source_type_ID = $this->mylookup('announcement_type',$title);


 drush_print_r($row);
  
  
  
  //return $nid;

}
}


