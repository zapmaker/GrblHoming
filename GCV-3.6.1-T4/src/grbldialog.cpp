/****************************************************************
 * grbldialog.cpp
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#include "grbldialog.h"
#include "ui_grbldialog.h"

GrblDialog::GrblDialog(QWidget *parent, GCode *gc) :
    QDialog(parent),
    gcode(gc),
    ui(new Ui::GrblDialog),
    tableRowCount(0)
{
    ui->setupUi(this);
    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(Cancel()));
    connect(ui->btnOk,SIGNAL(clicked()),this,SLOT(Ok()));
    connect(this, SIGNAL(sendGcodeAndGetResult(int, QString)), gcode, SLOT(sendGcodeAndGetResult(int, QString)));
    connect(gcode, SIGNAL(gcodeResult(int, QString)), this, SLOT(gcodeResult(int, QString)));

    ui->btnCancel->setEnabled(false);
    ui->btnOk->setEnabled(false);

    QStringList labels;
/// T4
    labels << tr("Rank");
    labels << tr("Value") << tr("Description");
    ui->table->setHorizontalHeaderLabels(labels);
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    ui->table->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
#else
    ui->table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
#endif
    ui->table->verticalHeader()->hide();
    ui->table->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->table->setShowGrid(true);
}

GrblDialog::~GrblDialog()
{
    delete ui;
}

void GrblDialog::getSettings()
{
/// T4 0.8a -> 0.8c !!!
    emit sendGcodeAndGetResult(GDLG_CMD_ID_GET, SETTINGS_COMMAND_V$$);
}

void GrblDialog::gcodeResult(int id, QString result)
{
    switch (id)
    {
    case GDLG_CMD_ID_GET:
    {
        originalValues.clear();
        changeFlags.clear();

        if (result.size() > 0)
        {
            /// #define REGEXP_SETTINGS_LINE    "(\\d+)\\s*=\\s*([\\w\\.]+)\\s*\\(([^\\)]*)\\)"
            QRegExp rx(QString("\\$") + REGEXP_SETTINGS_LINE);
            int pos = 0;
/// T4
            QStringList fieldRank;
            QStringList fieldValues;
            QStringList descriptions;
            while ((pos = rx.indexIn(result, pos)) != -1)
            {
                int matched = rx.matchedLength();
                //QString extracted = received.mid(pos, matched);
                pos += matched;

                if (rx.captureCount() > 0)
                {
                    QStringList list = rx.capturedTexts();
                    if (list.size() == 4)
                    {
/// T4
                        fieldRank.append(list.at(1));
                        fieldValues.append(list.at(2));
                        descriptions.append(list.at(3));
                    }
                }
            }

            tableRowCount = fieldValues.size() ;
            ui->table->setRowCount(0);
            /// 2 -> 3
            ui->table->setColumnCount(3);

            int i;
            for (i = 0; i < tableRowCount; i++)
            {
                ui->table->insertRow(i);

                QTableWidgetItem *descWidget0 = new QTableWidgetItem(fieldRank.at(i));
                descWidget0->setFlags(Qt::NoItemFlags);
                 ui->table->setItem(i, 0, descWidget0);

                ui->table->setItem(i, 1, new QTableWidgetItem(fieldValues.at(i)));

                QTableWidgetItem *descWidget2 = new QTableWidgetItem(descriptions.at(i));
                descWidget2->setFlags(Qt::NoItemFlags);

                ui->table->setItem(i, 2, descWidget2);

                ui->table->item(i, 0)->setFont(QFont("Tahoma",10,-1,false));
                ui->table->item(i, 1)->setFont(QFont("Tahoma",10,87,false));
                ui->table->item(i, 2)->setFont(QFont("Tahoma",10,-1,false));

                originalValues.append(fieldValues.at(i));
                changeFlags.append(false);
            }

            ui->table->resizeColumnsToContents();
            int colWidthValues = ui->table->columnWidth(1);
            ui->table->setColumnWidth(0, colWidthValues + 10);

            connect(ui->table,SIGNAL(cellChanged(int,int)),this,SLOT(changeValues(int,int)));
        }
        else
        {
            ui->table->setRowCount(0);
            ui->table->setColumnCount(3);
        }
        ui->btnCancel->setEnabled(true);
        ui->btnOk->setEnabled(true);
        break;
    }
    case GDLG_CMD_ID_SET:
        break;
    }
}

void GrblDialog::Cancel()
{
    this->close();
}

void GrblDialog::changeValues(int row, int col)
{
    Q_UNUSED(col);

    if ((ui->table->item(row,1)->text() != originalValues.at(row))
        && ui->table->item(row,1)->text().length() > 0)
    {
        changeFlags.replace(row, true);
    }
}

void GrblDialog::Ok()
{
    for(int i = 0; i < tableRowCount; i++)
    {
        if (changeFlags.at(i) == true)
        {
            QString strline = "$";
            strline.append(ui->table->item(i,0)->text());
            strline.append("=").append(ui->table->item(i,1)->text()).append('\r');
            emit sendGcodeAndGetResult(GDLG_CMD_ID_SET, strline);
        }
    }
    this->close();
}

