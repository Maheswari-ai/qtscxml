/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSTATEMACHINE module of the Qt Toolkit.
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

#ifndef QSTATEMACHINEQMLGLOBALS_P_H
#define QSTATEMACHINEQMLGLOBALS_P_H

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

#include <QtCore/qglobal.h>

QT_BEGIN_NAMESPACE

#if !defined(QT_STATIC)
#  if defined(QT_BUILD_STATEMACHINEQML_LIB)
#    define Q_STATEMACHINEQML_EXPORT Q_DECL_EXPORT
#  else
#    define Q_STATEMACHINEQML_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define Q_STATEMACHINEQML_EXPORT
#endif

#define Q_STATEMACHINEQML_PRIVATE_EXPORT Q_STATEMACHINEQML_EXPORT

QT_END_NAMESPACE

void Q_STATEMACHINEQML_PRIVATE_EXPORT qml_register_types_QtQml_StateMachine();

#endif // QSTATEMACHINEQMLGLOBALS_P_H
