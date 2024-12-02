#ifndef THEME_H
#define THEME_H

#include <QObject>

class Theme
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    Theme(QString background,QString foreground, QString primary, QString lightbackground, QString secondary, QString lightforeground);

    QString getBackground() const;
    void setBackground(const QString &newBackground);

    QString getForeground() const;
    void setForeground(const QString &newForeground);

    QString getPrimary() const;
    void setPrimary(const QString &newPrimary);

    QString getLightbackground() const;
    void setLightbackground(const QString &newLightbackground);

    QString getSecondary() const;
    void setSecondary(const QString &newSecondary);

    QString getLightforeground() const;
    void setLightforeground(const QString &newLightforeground);

private:
    QString _background;
    QString _foreground;
    QString _primary;
    QString _lightbackground;
    QString _secondary;
    QString _lightforeground;
};

#endif // THEME_H
