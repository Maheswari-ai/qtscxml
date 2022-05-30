/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
******************************************************************************/

#ifndef QHISTORYSTATE_P_H
#define QHISTORYSTATE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "private/qabstractstate_p.h"

#include <QtCore/qlist.h>

#include <QtStateMachine/qabstracttransition.h>
#include <QtStateMachine/qhistorystate.h>
#include <QtCore/private/qproperty_p.h>

QT_REQUIRE_CONFIG(statemachine);

QT_BEGIN_NAMESPACE

class QHistoryStatePrivate : public QAbstractStatePrivate
{
    Q_DECLARE_PUBLIC(QHistoryState)

public:
    QHistoryStatePrivate();

    static QHistoryStatePrivate *get(QHistoryState *q)
    { return q->d_func(); }

    void setDefaultTransition(QAbstractTransition* transition)
    {
        q_func()->setDefaultTransition(transition);
    }
    Q_OBJECT_COMPAT_PROPERTY_WITH_ARGS(QHistoryStatePrivate,
                                       QAbstractTransition*, defaultTransition,
                                       &QHistoryStatePrivate::setDefaultTransition, nullptr);

    void historyTypeChanged()
    {
        emit q_func()->historyTypeChanged(QHistoryState::QPrivateSignal());
    }
    Q_OBJECT_BINDABLE_PROPERTY(QHistoryStatePrivate, QHistoryState::HistoryType,
                               historyType, &QHistoryStatePrivate::historyTypeChanged);

    QList<QAbstractState*> configuration;
};

QT_END_NAMESPACE

#endif // QHISTORYSTATE_P_H
