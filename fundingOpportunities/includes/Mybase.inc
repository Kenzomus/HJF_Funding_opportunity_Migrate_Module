<?php
abstract class Mybase extends Migration {
  public function __construct() {
    parent::__construct();
$this->team = array(
      new MigrateTeamMember('HJF', 'indiaye@hjf.org',
                            t('Product Owner')),
      new MigrateTeamMember('Ibrahima', 'kenzomus@gmail.com',
                            t('Implementor')),
);
}
}