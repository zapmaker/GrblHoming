/****************************************************************
 * about.h
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include "definitions.h"

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT
    
public:
    explicit About(QWidget *parent = 0);
    ~About();
    
private:
    Ui::About *ui;
};

#endif // ABOUT_H
