#ifndef MEMORYSETTINGS_H
#define MEMORYSETTINGS_H

#include <QDialog>

namespace Ui {
class MemorySettings;
}

class MemorySettings : public QDialog
{
    Q_OBJECT

public:
    explicit MemorySettings(QWidget *parent = nullptr);
    ~MemorySettings();
    std::size_t getMemoryLimit();
    //static std::size_t memoryLimit;

private:
    Ui::MemorySettings *ui;
};

#endif // MEMORYSETTINGS_H
