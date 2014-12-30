HJF_Funding_opportunity_Migrate_Module
======================================

implementation of the migrate module to import data (funding opportunities, sponsors, RADS , programs ....i)n json from the filemaker database.

I. Installation
 1.Download the zip files and unzipped it or clone it to install it locally , at sites/all/modules or sites/all/modules/custom depending on your local configuration.
 if created with devdesk it will /docroot/sites/all/modules where you put your contributed module
 
 2.Enable the module by going to module in drupal GUI or using drush en (--better with drush cause it will download the dependencies modulke = migrate.
 


2.1.Enable it using drupal GUi , go to module and install it. It depends to Migrate module , in case you don't have it has to be downloaded and enabled as well on drupal.org (https://www.drupal.org/project/migrate)

2.2 You can use drush en fundingopportunities  to enable it and drush will automatically download the depedent module (Migrate if not already installed)

III. How to use it 
		
	Some context

 	1.We create a base class to extend the Migration class that come with Migrate module

	2.From the base We create sponsorMigrate, programMigration, RADS Migration, TypeMigration Classes they are all in the includes folder

	3.We set the class source using the json files included in the folder data/sources. ().
	You will have to change the file path if you have different configuration.
	
	To learn more about the implementation of migrate you can to https://www.drupal.org/node/415260

	4.1 If all sets , go to the drupal site /Content/Migrate you should see all the migrations implemented by the classes mentionned above.
	You can run the Migrate UI to start importing  , rollback ...

	4.2 you can use drush ms to see all the Migration , then drush mi (Name of the migration you want to run) or drush mr (Name of the migration you want to run ) to rollback . 
	For more drush command 
	check drush help --filter="migrate"
	
