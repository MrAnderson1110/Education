#include "apphistory.h"

#include <QDebug>

AppHistory *AppHistory::instance()
{
    if(!m_instance)
        m_instance = new AppHistory;

    return m_instance;
}

QObject *AppHistory::singletonTypeProvider(QQmlEngine *, QJSEngine *)
{
    return m_instance;
}

QModelIndex AppHistory::index(int row, int column, const QModelIndex &parent) const
{

}

QModelIndex AppHistory::parent(const QModelIndex &child) const
{

}

int AppHistory::rowCount(const QModelIndex &parent) const
{

}

int AppHistory::columnCount(const QModelIndex &parent) const
{

}

QVariant AppHistory::data(const QModelIndex &index, int role) const
{

}

Snapshot *AppHistory::pop()
{
    Snapshot *snap = m_history.takeFirst();
    qDebug() << *snap;
    return snap;
}

void AppHistory::push(Snapshot *snapshot)
{
    qDebug() << *snapshot;
    m_history.prepend(snapshot);
}

AppHistory *AppHistory::m_instance = nullptr;

AppHistory::AppHistory(QObject *parent)
    : QAbstractListModel(parent)
    , m_history()
{

}

#include <BasicPiece>

Snapshot::Snapshot()
    : m_states()
    , m_internal()
{
    reset();
}

Snapshot::Snapshot(State *state)
    : m_states()
    , m_internal()
{
    m_states << state;
    reset();
}

Snapshot::~Snapshot()
{
    qDeleteAll(m_states);
}

void Snapshot::add(State *state)
{
    m_states << state;
    reset();
}

State *Snapshot::next()
{
    if(m_internal == m_states.end())
        return nullptr;

    State *cur = *m_internal;
    ++m_internal;
    return cur;
}

void Snapshot::reset()
{
    m_internal = m_states.begin();
}

Snapshot::operator QString()
{
    QString str;
    for(State *state : qAsConst(m_states)) {
        QString command = state->owner()->command() == BasicPiece::White ? "W" : "B";

        QString pieceName;
        switch (state->owner()->type()) {
        case BasicPiece::King:
            pieceName = "Kg";
            break;
        case BasicPiece::Queen:
            pieceName = "Q";
            break;
        case BasicPiece::Bishop:
            pieceName = "B";
            break;
        case BasicPiece::Knight:
            pieceName = "Kn";
            break;
        case BasicPiece::Rook:
            pieceName = "R";
            break;
        case BasicPiece::Pawn:
            pieceName = "P";
            break;
        default:
            return str;
        }

        QString fromMove;
        switch(state->from().y()) {
        case 0:
            fromMove = QString("A%1").arg(7 - state->from().x() + 1);
            break;
        case 1:
            fromMove = QString("B%1").arg(7 - state->from().x() + 1);
            break;
        case 2:
            fromMove = QString("C%1").arg(7 - state->from().x() + 1);
            break;
        case 3:
            fromMove = QString("D%1").arg(7 - state->from().x() + 1);
            break;
        case 4:
            fromMove = QString("E%1").arg(7 - state->from().x() + 1);
            break;
        case 5:
            fromMove = QString("F%1").arg(7 - state->from().x() + 1);
            break;
        case 6:
            fromMove = QString("G%1").arg(7 - state->from().x() + 1);
            break;
        case 7:
            fromMove = QString("H%1").arg(7 - state->from().x() + 1);
            break;
        default:
            return str;
        }

        QString toMove;
        switch(state->to().y()) {
        case 0:
            toMove = QString("A%1").arg(7 - state->to().x() + 1);
            break;
        case 1:
            toMove = QString("B%1").arg(7 - state->to().x() + 1);
            break;
        case 2:
            toMove = QString("C%1").arg(7 - state->to().x() + 1);
            break;
        case 3:
            toMove = QString("D%1").arg(7 - state->to().x() + 1);
            break;
        case 4:
            toMove = QString("E%1").arg(7 - state->to().x() + 1);
            break;
        case 5:
            toMove = QString("F%1").arg(7 - state->to().x() + 1);
            break;
        case 6:
            toMove = QString("G%1").arg(7 - state->to().x() + 1);
            break;
        case 7:
            toMove = QString("H%1").arg(7 - state->to().x() + 1);
            break;
        default:
            return str;
        }

        str.append(command).append(": ").append(pieceName).append("-").append(fromMove).append("x").append(toMove).append(" ");
    }

    return str;
}

QList<State *> Snapshot::states() const
{
    return m_states;
}

BasicPiece *State::owner() const
{
    return m_owner;
}

Move State::from() const
{
    return m_from;
}

Move State::to() const
{
    return m_to;
}

State::State(BasicPiece *owner, const Move &from, const Move &to, BasicPiece *defeated)
    : m_owner(owner)
    , m_defeated(nullptr)
    , m_from(from)
    , m_to(to)
{

}

State::~State()
{

}

