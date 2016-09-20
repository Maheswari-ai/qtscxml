/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtScxml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSCXMLINVOKABLESERVICE_H
#define QSCXMLINVOKABLESERVICE_H

#include "qscxmldatamodel.h"
#include <QtCore/qstring.h>

QT_BEGIN_NAMESPACE

class QScxmlEvent;
class QScxmlStateMachine;
class QScxmlInvokableServiceFactory;

class QScxmlInvokableServicePrivate;
class Q_SCXML_EXPORT QScxmlInvokableService : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QScxmlInvokableService)
    Q_PROPERTY(QScxmlStateMachine *parentStateMachine READ parentStateMachine CONSTANT)
    Q_PROPERTY(bool autoforward READ autoforward CONSTANT)
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)

public:
    QScxmlInvokableService(QScxmlInvokableServiceFactory *factory,
                           QScxmlStateMachine *parentStateMachine,
                           QObject *parent = nullptr);

    bool autoforward() const;
    QScxmlStateMachine *parentStateMachine() const;

    virtual bool start() = 0;
    virtual QString id() const = 0;
    virtual QString name() const = 0;
    virtual void postEvent(QScxmlEvent *event) = 0;

    void finalize();

protected:
    QScxmlInvokableServiceFactory *factory() const;
    QScxmlInvokableService(QScxmlInvokableServicePrivate &dd, QObject *parent = nullptr);
};

class QScxmlInvokableServiceFactoryPrivate;
class Q_SCXML_EXPORT QScxmlInvokableServiceFactory
{
public:
    QScxmlInvokableServiceFactory(QScxmlExecutableContent::StringId invokeLocation,
                                  QScxmlExecutableContent::EvaluatorId srcexpr,
                                  QScxmlExecutableContent::StringId id,
                                  QScxmlExecutableContent::StringId idPrefix,
                                  QScxmlExecutableContent::StringId idlocation,
                                  const QVector<QScxmlExecutableContent::StringId> &namelist,
                                  bool autoforward,
                                  const QVector<QScxmlExecutableContent::ParameterInfo> &params,
                                  QScxmlExecutableContent::ContainerId finalizeContent);
    virtual ~QScxmlInvokableServiceFactory();

    virtual QScxmlInvokableService *invoke(QScxmlStateMachine *parentStateMachine) = 0;

public: // callbacks from the service:
    QString calculateSrcexpr(QScxmlStateMachine *parent, bool *ok) const;
    QString calculateId(QScxmlStateMachine *parent, bool *ok) const;
    QVariantMap calculateData(QScxmlStateMachine *parent, bool *ok) const;
    bool autoforward() const;
    QScxmlExecutableContent::ContainerId finalizeContent() const;

private:
    QScxmlInvokableServiceFactoryPrivate *d;
};

class QScxmlScxmlServicePrivate;
class Q_SCXML_EXPORT QScxmlScxmlService: public QScxmlInvokableService
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QScxmlScxmlService)
    Q_PROPERTY(QScxmlStateMachine *stateMachine READ stateMachine CONSTANT)
public:
    QScxmlScxmlService(QScxmlInvokableServiceFactory *factory, QScxmlStateMachine *stateMachine,
                       QScxmlStateMachine *parentStateMachine, QObject *parent = nullptr);

    bool start() Q_DECL_OVERRIDE;
    QString id() const Q_DECL_OVERRIDE;
    QString name() const Q_DECL_OVERRIDE;
    void postEvent(QScxmlEvent *event) Q_DECL_OVERRIDE;

    QScxmlStateMachine *stateMachine() const;
};

class Q_SCXML_EXPORT QScxmlScxmlServiceFactory: public QScxmlInvokableServiceFactory
{
public:
    QScxmlScxmlServiceFactory(QScxmlExecutableContent::StringId invokeLocation,
                              QScxmlExecutableContent::EvaluatorId srcexpr,
                              QScxmlExecutableContent::StringId id,
                              QScxmlExecutableContent::StringId idPrefix,
                              QScxmlExecutableContent::StringId idlocation,
                              const QVector<QScxmlExecutableContent::StringId> &namelist,
                              bool doAutoforward,
                              const QVector<QScxmlExecutableContent::ParameterInfo> &params,
                              QScxmlExecutableContent::ContainerId finalize);

protected:
    QScxmlScxmlService *invokeDynamic(QScxmlStateMachine *parentStateMachine,
                                      const QString &sourceUrl);
    QScxmlScxmlService *invokeStatic(QScxmlStateMachine *childStateMachine,
                                     QScxmlStateMachine *parentStateMachine);
};

template<class T>
class QScxmlStaticScxmlServiceFactory: public QScxmlScxmlServiceFactory
{
public:
    QScxmlStaticScxmlServiceFactory(QScxmlExecutableContent::StringId invokeLocation,
                             QScxmlExecutableContent::StringId id,
                             QScxmlExecutableContent::StringId idPrefix,
                             QScxmlExecutableContent::StringId idlocation,
                             const QVector<QScxmlExecutableContent::StringId> &namelist,
                             bool doAutoforward,
                             const QVector<QScxmlExecutableContent::ParameterInfo> &params,
                             QScxmlExecutableContent::ContainerId finalize)
        : QScxmlScxmlServiceFactory(invokeLocation, QScxmlExecutableContent::NoInstruction,
                                             id, idPrefix, idlocation, namelist, doAutoforward,
                                             params, finalize)
    {}

    QScxmlInvokableService *invoke(QScxmlStateMachine *parentStateMachine) Q_DECL_OVERRIDE
    {
        return invokeStatic(new T, parentStateMachine);
    }
};

class Q_SCXML_EXPORT QScxmlDynamicScxmlServiceFactory: public QScxmlScxmlServiceFactory
{
public:
    QScxmlDynamicScxmlServiceFactory(QScxmlExecutableContent::StringId invokeLocation,
                              QScxmlExecutableContent::EvaluatorId srcexpr,
                              QScxmlExecutableContent::StringId id,
                              QScxmlExecutableContent::StringId idPrefix,
                              QScxmlExecutableContent::StringId idlocation,
                              const QVector<QScxmlExecutableContent::StringId> &namelist,
                              bool doAutoforward,
                              const QVector<QScxmlExecutableContent::ParameterInfo> &params,
                              QScxmlExecutableContent::ContainerId finalize)
        : QScxmlScxmlServiceFactory(invokeLocation, srcexpr, id, idPrefix, idlocation,
                                             namelist, doAutoforward, params, finalize)
    {}

    QScxmlInvokableService *invoke(QScxmlStateMachine *parentStateMachine) Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QScxmlInvokableService *)

#endif // QSCXMLINVOKABLESERVICE_H
