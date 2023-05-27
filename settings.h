#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_apply_btn_clicked();

signals:
    void apply(QString,int);

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
