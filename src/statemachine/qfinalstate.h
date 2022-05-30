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

#ifndef QFINALSTATE_H
#define QFINALSTATE_H

#include <QtStateMachine/qabstractstate.h>

QT_REQUIRE_CONFIG(statemachine);

QT_BEGIN_NAMESPACE

class QFinalStatePrivate;
class Q_STATEMACHINE_EXPORT QFinalState : public QAbstractState
{
    Q_OBJECT
public:
    QFinalState(QState *parent = nullptr);
    ~QFinalState();

protected:
    void onEntry(QEvent *event) override;
    void onExit(QEvent *event) override;

    bool event(QEvent *e) override;

protected:
    explicit QFinalState(QFinalStatePrivate &dd, QState *parent);

private:
    Q_DISABLE_COPY(QFinalState)
    Q_DECLARE_PRIVATE(QFinalState)
};

QT_END_NAMESPACE

#endif
