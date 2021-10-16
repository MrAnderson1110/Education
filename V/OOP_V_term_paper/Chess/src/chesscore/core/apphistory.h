#ifndef APPHISTORY_H
#define APPHISTORY_H

#include "chesscore_global.h"

#include "mover.h"

class CHESSCORE_EXPORT State
{
public:
    State(BasicPiece *owner,
          const Move &from,
          const Move &to,
          BasicPiece *defeated = nullptr);
    ~State();

    BasicPiece *owner() const;
    Move from() const;
    Move to() const;

private:
    BasicPiece *m_owner;
    BasicPiece *m_defeated;
    Move m_from;
    Move m_to;
};

class CHESSCORE_EXPORT Snapshot
{
public:
    Snapshot();
    Snapshot(State *state);
    ~Snapshot();

    void add(State *state);
    State *next();
    void reset();

    operator QString();

    QList<State *> states() const;

private:
    QList<State *> m_states;
    QList<State *>::iterator m_internal;
};

#include <QAbstractListModel>
#include <QStack>

#define appHistory AppHistory::instance()

class QQmlEngine;
class QJSEngine;

class CHESSCORE_EXPORT AppHistory : public QAbstractListModel
{
public:
    static AppHistory *instance();
    static QObject *singletonTypeProvider(QQmlEngine *, QJSEngine *);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    Snapshot *pop();
    void push(Snapshot *snapshot);

private:
    explicit AppHistory(QObject *parent = nullptr);

private:
    static AppHistory *m_instance;
    QList<Snapshot *> m_history;
};

#endif // APPHISTORY_H
