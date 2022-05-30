/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWidgets module of the Qt Toolkit.
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

#ifndef QBASICMOUSEEVENTTRANSITION_P_H
#define QBASICMOUSEEVENTTRANSITION_P_H

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

#include <QtGui/qevent.h>
#include <QtStateMachine/qabstracttransition.h>

QT_REQUIRE_CONFIG(qeventtransition);

QT_BEGIN_NAMESPACE

class QPainterPath;

class QBasicMouseEventTransitionPrivate;
class Q_AUTOTEST_EXPORT QBasicMouseEventTransition : public QAbstractTransition
{
    Q_OBJECT
public:
    QBasicMouseEventTransition(QState *sourceState = nullptr);
    QBasicMouseEventTransition(QEvent::Type type, Qt::MouseButton button,
                               QState *sourceState = nullptr);
    ~QBasicMouseEventTransition();

    QEvent::Type eventType() const;
    void setEventType(QEvent::Type type);

    Qt::MouseButton button() const;
    void setButton(Qt::MouseButton button);
    QBindable<Qt::MouseButton> bindableButton();

    Qt::KeyboardModifiers modifierMask() const;
    void setModifierMask(Qt::KeyboardModifiers modifiers);
    QBindable<Qt::KeyboardModifiers> bindableModifierMask();

    QPainterPath hitTestPath() const;
    void setHitTestPath(const QPainterPath &path);

protected:
    bool eventTest(QEvent *event) override;
    void onTransition(QEvent *) override;

private:
    Q_DISABLE_COPY_MOVE(QBasicMouseEventTransition)
    Q_DECLARE_PRIVATE(QBasicMouseEventTransition)
};

QT_END_NAMESPACE

#endif
