// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_bitcoinaddressVALIDATOR_H
#define BITCOIN_QT_bitcoinaddressVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class bitcoinaddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit bitcoinaddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Bitcoin address widget validator, checks for a valid bitcoin address.
 */
class bitcoinaddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit bitcoinaddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // BITCOIN_QT_bitcoinaddressVALIDATOR_H
