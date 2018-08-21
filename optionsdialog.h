#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QString>
#include <QHash>
#include <QFrame>
#include "commonunits.h"
#include "rosco.h"

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    OptionsDialog(QString title, QWidget *parent = 0);
    mems_ver getMemsVersion() { return m_memsVersion; }
    bool getMemsVersionChanged() { return m_memsVersionChanged; }
    TemperatureUnits getTemperatureUnits() { return m_tempUnits; }

protected:
    void accept();

private:
    QGridLayout *m_grid;
    QLabel *m_memsVersionLabel;
    QComboBox *m_memsVersionBox;

    QLabel *m_temperatureUnitsLabel;
    QComboBox *m_temperatureUnitsBox;

    QFrame *m_horizontalLineA;

    QCheckBox *m_refreshFuelMapCheckbox;

    QPushButton *m_okButton;
    QPushButton *m_cancelButton;

    mems_ver m_memsVersion;
    TemperatureUnits m_tempUnits;

    bool m_memsVersionChanged;

    const QString m_settingsFileName;
    const QString m_settingsGroupName;

    const QString m_settingMemsVersion;
    const QString m_settingTemperatureUnits;

    void setupWidgets();
    void readSettings();
    void writeSettings();
};

#endif // OPTIONSDIALOG_H

