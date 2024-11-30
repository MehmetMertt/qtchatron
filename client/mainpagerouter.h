#include <QObject>
#include <QtQml>

class MainPageRouter : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(MainArea currentItem READ currentItem WRITE setCurrentItem NOTIFY currentItemChanged FINAL)
    Q_PROPERTY(QString topbarTitle READ topbarTitle WRITE setTopbarTitle NOTIFY topbarTitleChanged FINAL)
    Q_PROPERTY(QString topbarType READ topbarType NOTIFY topbarTypeChanged FINAL)

public:
    explicit MainPageRouter(QObject *parent = nullptr);

    enum MainArea {
        DM_OVERVIEW,
        CHANNEL,
        CHAT
    };
    Q_ENUM(MainArea);

    MainArea currentItem() const;

    Q_INVOKABLE void setCurrentItem(MainArea newCurrentItem, QString newTitle = nullptr);
    Q_INVOKABLE void setTopbarTitle(QString newTitle);
    Q_INVOKABLE void back();
    Q_INVOKABLE void triggerBack();

    QString topbarTitle() const;
    QString topbarType() const;

private:
    MainArea _currentItem;
    QString _topbarTitle;
    QString _topbarType;
    QStack<MainArea> _navigationStack;

signals:
    void currentItemChanged();
    void topbarTitleChanged();
    void topbarTypeChanged();
    void backButtonPressed();
};
