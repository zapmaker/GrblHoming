/****************************************************************
 * about.cpp
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#include "about.h"
#include "version.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    QString title = GRBL_CONTROLLER_NAME_AND_VERSION ;
    title += "\n";
    title += VERSION_BUILD ;
    ui->labelProductAndVersion->setText(title);
}

About::~About()
{
    delete ui;
}
