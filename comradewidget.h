#ifndef COMRADEWIDGET_H
#define COMRADEWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class comradeWidget; }
QT_END_NAMESPACE

class comradeWidget : public QWidget
{
    Q_OBJECT

public:
    comradeWidget(QWidget *parent = nullptr);
    ~comradeWidget();

private slots:
    void on_startButton_clicked();
    void writeData1(const QByteArray &data);
    void writeData2(const QByteArray &data);

private:
    void readData1();
    void readData2();

    Ui::comradeWidget *ui;
};
#endif // COMRADEWIDGET_H
