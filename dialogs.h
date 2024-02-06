#ifndef DIALOGS_H
#define DIALOGS_H

#include <QDialog>
#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

class Dialog : public QDialog
{
public:
    Dialog(const QStringList& items, QString message = "Vyberte slozitost:")
    {
        setLayout(new QVBoxLayout);
        box = new QComboBox;
        box->addItems(items);
        box->setCurrentIndex(1);
        msgLabel = new QLabel(message);
        layout()->addWidget(msgLabel);
        layout()->addWidget(box);
        QPushButton* ok = new QPushButton("ok");
        layout()->addWidget(ok);
        connect(ok, &QPushButton::clicked, this, [this]()
        {
           accept();
        });
    }
    QComboBox* comboBox() { return box; }

private:
    QComboBox* box;
    QLabel * msgLabel;

};

#endif // DIALOGS_H
