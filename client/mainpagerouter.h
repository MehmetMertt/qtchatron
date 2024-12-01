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
    Q_PROPERTY(bool showChannelInfo READ showChannelInfo WRITE setShowChannelInfo NOTIFY showChannelInfoChanged FINAL)
    Q_PROPERTY(int selectedPageID READ selectedPageID WRITE setSelectedPageID NOTIFY selectedPageIDChanged FINAL)
public:
    explicit MainPageRouter(QObject *parent = nullptr);

    enum MainArea {
        DM_OVERVIEW,
        CHANNEL,
        CHAT,
        SETTINGS
    };
    Q_ENUM(MainArea);

    MainArea currentItem() const;

    Q_INVOKABLE void setCurrentItem(MainArea newCurrentItem, QString newTitle = nullptr);
    Q_INVOKABLE void setTopbarTitle(QString newTitle);
    Q_INVOKABLE void triggerBack();
    Q_INVOKABLE void closeNewChatPopup();
    Q_INVOKABLE void setShowChannelInfo(bool newShowChannelInfo);
    Q_INVOKABLE void setSelectedPageID(int newSelectedPageID);

    QString topbarTitle() const;
    QString topbarType() const;

    bool showChannelInfo() const;


    int selectedPageID() const;


private:
    MainArea _currentItem;
    QString _topbarTitle;
    QString _topbarType;
    bool _showChannelInfo;
    int _selectedPageID;


signals:
    void currentItemChanged();
    void topbarTitleChanged();
    void topbarTypeChanged();
    void backButtonPressed();
    void closePopup();
    void showChannelInfoChanged();
    void selectedPageIDChanged();
};
