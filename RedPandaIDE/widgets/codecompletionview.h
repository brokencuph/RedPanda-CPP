#ifndef CODECOMPLETIONVIEW_H
#define CODECOMPLETIONVIEW_H

#include <QListView>
#include <QWidget>
#include "parser/cppparser.h"

using KeyPressedCallback = std::function<bool (QKeyEvent *)>;

class CodeCompletionListView: public QListView {
    Q_OBJECT
public:
    explicit CodeCompletionListView(QWidget *parent = nullptr);

    // QWidget interface
    const KeyPressedCallback &keypressedCallback() const;
    void setKeypressedCallback(const KeyPressedCallback &newKeypressedCallback);

protected:
    void keyPressEvent(QKeyEvent *event) override;
private:
    KeyPressedCallback mKeypressedCallback;
};

class CodeCompletionListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit CodeCompletionListModel(StatementList* statements,QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void notifyUpdated();
private:
    const StatementList* mStatements;

};

class CodeCompletionView : public QWidget
{
    Q_OBJECT

public:
    explicit CodeCompletionView(QWidget *parent = nullptr);
    ~CodeCompletionView();

    void setKeypressedCallback(const KeyPressedCallback &newKeypressedCallback);
    void prepareSearch(const QString& phrase, const QString& filename, int line);
    bool search(const QString& phrase, bool autoHideOnSingleResult);


private:
    void addChildren(PStatement scopeStatement, const QString& fileName,
                     int line);
    void addStatement(PStatement statement, const QString& fileName, int line);
    void filterList(const QString& member);
    void getCompletionFor(const QString& fileName,const QString& phrase, int line);
    bool isIncluded(const QString& fileName);
private:
    CodeCompletionListView * mListView;
    CodeCompletionListModel* mModel;
    QList<PCodeIns> mCodeInsList; //(Code template list)
    //QList<PStatement> mCodeInsStatements; //temporary (user code template) statements created when show code suggestion
    PCppParser mParser;
    StatementList mFullCompletionStatementList;
    StatementList mCompletionStatementList;
    int mShowCount;
    bool mOnlyGlobals;
    PStatement mCurrentStatement;
    QSet<QString> mIncludedFiles;
    QSet<QString> mUsings;
    QSet<QString> mAddedStatements;
    QString mPhrase;
    QHash<QString,int> mSymbolUsage;
    bool mRecordUsage;
    bool mShowKeywords;
    bool mShowCodeIns;
    bool mIgnoreCase;
    QRecursiveMutex mMutex;
    bool mSortByScope;
    bool mUseCppKeyword;


    // QWidget interface
protected:
    void hideEvent(QHideEvent *event) override;
};

#endif // CODECOMPLETIONVIEW_H
