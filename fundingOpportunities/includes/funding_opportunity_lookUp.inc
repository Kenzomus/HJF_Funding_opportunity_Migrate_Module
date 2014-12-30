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
    //$json_file = fopen("\\data\\sources\\mylist.json", "r");
    //file_get_contents('data/sources/mylist.json');
    //$mydata= file_get_contents("http://docroot.local:8083/sites/all/modules/fundingopportunities/data/sources/mylist.json"); 
    //$json=json_decode( preg_replace('/[\x00-\x1F\x80-\xFF]/', '', $mydata), true );
    
    $mjason = "/Users/indiaye/bkup_oct_17_14/hjf/docroot/sites/all/modules/fundingOpportunities/data/sources/funding_opportunity_look_up";
    //$mjason="/Users/indiaye/bkup_oct_17_14/hjf/docroot/sites/all/modules/fundingOpportunities/data/sources/latestjason.json";
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
 				->sourceMigration('sponsorMigration');
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
 								->separator(',')
 			->callbacks($this, 'mylookup');




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
  
function mylookup($title){
$type= 'RADS';
$status= 1;
$result = db_query("SELECT nid,created FROM {node} Where type=:type and status =:status and title=:title ",

array(':type'=>$type, ':status' =>1,':title'=>'title'));

 //Result is returned as a iterable object that returns a stdClass object on each iteration
if(!empty($result)){
foreach ($result as $record) {
  // Perform operations on $record->title, etc. here.
  $nid= $record->nid ;
//echo $record->title."<br/>";
//return $record->nid;
//"<br/>";
//return $result;
//$nid = $result->fetchfield();

//$this->$row->source_RADS_ID= $result;
//}

//}
//}
//class MigrateEntityReferenceFieldHandler extends MigrateSimpleFieldHandler {
  //public function __construct() {
    //parent::__construct(array(
     // 'value_key' => 'target_id', 
     // 'skip_empty' => TRUE,
    //)//);

    //$//this->registerTypes(array('entityreference'));
  }
  return  $nid;
}



//public function prepare_row($row){

//$input_title= $row->source_RADS_ID;
//$type= 'RADS';
//$status= 1;
//$result = db_query("SELECT nid,created FROM {node} Where type=:type and status =:status and title=:title ",

//array(':type'=>$type, ':status' =>1,':title'=>'$input_title',));

// Result is returned as a iterable object that returns a stdClass object on each iteration
//if(!empty($result)){

//foreach ($result as $record) {
  // Perform operations on $record->title, etc. here.
  
//echo
//$nid= $record->nid ;
//return $record->nid."<br/>";

//return $row->source_RADS_ID= $nid;
 
//drush_print_r($row);


}
}
//}


