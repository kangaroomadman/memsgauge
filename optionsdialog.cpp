#include <QSettings>
#include "optionsdialog.h"

/**
 * Constructor; sets up the options-dialog UI and sets settings-file field names.
 */
OptionsDialog::OptionsDialog(QString title, QWidget * parent):QDialog(parent),
m_memsVersionChanged(false),
m_settingsGroupName("Settings"), m_settingMemsVersion("MemsVersion"), m_settingTemperatureUnits("TemperatureUnits")
{
  this->setWindowTitle(title);
  readSettings();
  setupWidgets();
}

/**
 * Instantiates widgets, connects to their signals, and places them on the form.
 */
void OptionsDialog::setupWidgets()
{
  unsigned int row = 0;

  m_grid = new QGridLayout(this);

  m_memsVersionLabel = new QLabel("MEMS version:", this);
  m_memsVersionBox = new QComboBox(this);

  m_temperatureUnitsLabel = new QLabel("Temperature units:", this);
  m_temperatureUnitsBox = new QComboBox(this);

  m_horizontalLineA = new QFrame(this);
  m_horizontalLineA->setFrameShape(QFrame::HLine);
  m_horizontalLineA->setFrameShadow(QFrame::Sunken);

  m_okButton = new QPushButton("OK", this);
  m_cancelButton = new QPushButton("Cancel", this);

  m_memsVersionBox->addItem("1.6");
  m_memsVersionBox->addItem("2J");
  m_memsVersionBox->setEditable(false);
  m_memsVersionBox->setCurrentIndex((int)m_memsVersion);

  m_temperatureUnitsBox->setEditable(false);
  m_temperatureUnitsBox->addItem("Fahrenheit");
  m_temperatureUnitsBox->addItem("Celsius");
  m_temperatureUnitsBox->setCurrentIndex((int)m_tempUnits);

  m_grid->addWidget(m_memsVersionLabel, row, 0);
  m_grid->addWidget(m_memsVersionBox, row++, 1);

  m_grid->addWidget(m_temperatureUnitsLabel, row, 0);
  m_grid->addWidget(m_temperatureUnitsBox, row++, 1);

  m_grid->addWidget(m_horizontalLineA, row++, 0, 1, 2);

  m_grid->addWidget(m_okButton, row, 0);
  m_grid->addWidget(m_cancelButton, row++, 1);

  connect(m_okButton, SIGNAL(clicked()), this, SLOT(accept()));
  connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

/**
 * Reads the new settings from the form controls.
 */
void OptionsDialog::accept()
{
  const mems_ver newMemsVersion = (mems_ver)m_memsVersionBox->currentIndex();

  // set a flag if the mems version has been changed;
  // the main application needs to know if it should
  // reconnect to the ECU using the updated version
  if (m_memsVersion != newMemsVersion)
  {
    m_memsVersion = newMemsVersion;
    m_memsVersionChanged = true;
  }
  else
  {
    m_memsVersionChanged = false;
  }

  m_tempUnits = (TemperatureUnits) (m_temperatureUnitsBox->currentIndex());

  writeSettings();
  done(QDialog::Accepted);
}

/**
 * Reads values for all the settings (either from the settings file, or by return defaults.)
 */
void OptionsDialog::readSettings()
{
  QSettings settings(QSettings::IniFormat, QSettings::UserScope, PROJECTNAME);

  settings.beginGroup(m_settingsGroupName);
  m_memsVersion = (mems_ver) settings.value(m_settingMemsVersion, MEMS_Version_16).toInt();
  m_tempUnits = (TemperatureUnits) (settings.value(m_settingTemperatureUnits, Fahrenheit).toInt());

  settings.endGroup();
}

/**
 * Writes settings out to a file on disk.
 */
void OptionsDialog::writeSettings()
{
  QSettings settings(QSettings::IniFormat, QSettings::UserScope, PROJECTNAME);

  settings.beginGroup(m_settingsGroupName);
  settings.setValue(m_settingMemsVersion, m_memsVersion);
  settings.setValue(m_settingTemperatureUnits, m_tempUnits);

  settings.endGroup();
}
