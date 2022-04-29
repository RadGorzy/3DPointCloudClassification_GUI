#include "view/memorySettings.h"
#include "ui_memorySettings.h"

MemorySettings::MemorySettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemorySettings)
{
    ui->setupUi(this);
}

MemorySettings::~MemorySettings()
{
    delete ui;
}
//std::size_t MemorySettings::memoryLimit=10000;
std::size_t MemorySettings::getMemoryLimit(){
    return static_cast<std::size_t>(this->ui->memoryLimit_doubleSpinBox->value());
}
