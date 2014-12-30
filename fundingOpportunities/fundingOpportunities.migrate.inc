<?php
function fundingOpportunities_migrate_api()
{
$api = array(
    'api' => 2,
    'groups' => array(
      'Funding' => array(
        'title' => t('Funding opportunities'),
        
      ),
    ),
    'migrations' => array(
      'Opportunities' => array(
        'class_name' => 'opportunities',
        'group_name' => 'Funding',
      ),
     'sponsorMigration'=> array(
        'class_name' => 'sponsorsMigration',
        'group_name' => 'Funding',
      ),
      'programMigration'=>array(
      'class_name' => 'programMigration',
      'group_name' => 'funding',

    ),
    'typeMigration'=>array(
      'class_name' => 'typeMigration',
      'group_name' => 'funding',
      
      ),
   'radsMigration'=>array(
      'class_name' => 'radsMigration',
      'group_name' => 'funding',
      
      ),
      'funding_opportunity_lookUp'=>array(
      'class_name' => 'funding_opportunity_lookUp',
      'group_name' => 'funding',
      
      ),
      ),
      
	);  
  return $api;



}
