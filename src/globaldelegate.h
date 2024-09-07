#ifndef GLOBALDELEGATE_H
#define GLOBALDELEGATE_H

#include <QObject>
#include <QComboBox>
#include <QSpinBox>
#include <QSqlTableModel>
#include <QItemDelegate>

class ReadOnlyDelegate : public QItemDelegate
{
public:
    ReadOnlyDelegate(QWidget *parent=0):QItemDelegate(parent){}

     QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
  const QModelIndex &index) const override
    {
        Q_UNUSED(parent) Q_UNUSED(index) Q_UNUSED(option)
        return nullptr;
    }

     void setEditorData(QWidget *editor, const QModelIndex &index) const{
        Q_UNUSED(editor) Q_UNUSED(index)
     }
     void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
        Q_UNUSED(editor) Q_UNUSED(model) Q_UNUSED(index)
     }
     void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
  const QModelIndex &index) const{
        Q_UNUSED(editor) Q_UNUSED(option) Q_UNUSED(index)
     }

};

class EvaluareDelegate : public QItemDelegate
{
 public:
     EvaluareDelegate(QWidget *parent=0):QItemDelegate(parent){}

     QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const override
     {
        Q_UNUSED(option)


        QModelIndex statusIndex=index.model()->index(index.row(),8);
        QModelIndex efftIndex=index.model()->index(index.row(),9);
        QModelIndex mothIndex=index.model()->index(index.row(),10);
        QModelIndex conIndxe=index.model()->index(index.row(),11);

        if(index.model()->data(statusIndex).isNull() || index.model()->data(efftIndex).isNull()||
            index.model()->data(mothIndex).isNull() || index.model()->data(conIndxe).isNull())
        {
            QSpinBox *box=new QSpinBox(parent);
            box->setMinimum(0);
            box->setSingleStep(1);

            int nowCol=index.column();

            if(nowCol==8) box->setMaximum(25);
            else if(nowCol==9) box->setMaximum(30);
            else if(nowCol==10) box->setMaximum(30);
            else if(nowCol==11) box->setMaximum(15);

            return box;
        }
        else
        return nullptr;
     }

     void setEditorData(QWidget *editor, const QModelIndex &index) const{
        QVariant data=index.model()->data(index,Qt::EditRole);
        QSpinBox *spinbox=static_cast<QSpinBox*>(editor);
        if(spinbox==nullptr) return;
        if(data.isNull())
        spinbox->setValue(0);
        else{
            int num=data.toInt();
            spinbox->setValue(num);
        }
     }
     void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
        QSpinBox *spinbox=static_cast<QSpinBox*>(editor);
        if(spinbox==nullptr) return;
        model->setData(index,spinbox->value(),Qt::EditRole);
     }
     void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const{
        Q_UNUSED(index)

        QSpinBox *spinbox=static_cast<QSpinBox*>(editor);
        if(spinbox==nullptr) return;
        spinbox->setGeometry(option.rect);
     }

};

class PassDelegate:public QItemDelegate
{
public:
    PassDelegate(QWidget *parent=0):QItemDelegate(parent){}

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override
    {
                Q_UNUSED(index) Q_UNUSED(option)
                QComboBox *combox=new QComboBox(parent);
                combox->addItem("未通过");
                combox->addItem("通过");
                return combox;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const{
           QVariant data=index.model()->data(index,Qt::EditRole);
           QComboBox *combox=static_cast<QComboBox*>(editor);
           if(data.isNull())
               combox->setCurrentText(0);
           else{
               int num=data.toInt();
               if(num==0) combox->setCurrentIndex(0);
               else combox->setCurrentIndex(1);
           }
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
        QComboBox *combox=static_cast<QComboBox*>(editor);
        int num=combox->currentIndex();
        if(num==0) model->setData(index,0);
        else model->setData(index,1);

    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const{
        Q_UNUSED(index)
        QComboBox *combox=static_cast<QComboBox*>(editor);
        combox->setGeometry(option.rect);
    }

};

#endif // GLOBALDELEGATE_H
