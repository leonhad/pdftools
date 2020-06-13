/*
 * PDF Tools.
 * Copyright (C) 2012-2016 Leonardo Alves da Costa
 * mailto:leonhad AT gmail DOT com
 *
 * PDF Tools is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * PDF Tools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace parser
{
/**
 * Defines the token type.
 */
enum class TokenType
{
    /**
     * The end of file.
     */
    ENDFILE,

    /**
     * A error.
     */
    ERROR,

    /**
     * Indicates the start of an array.
     *
     */
    START_ARRAY,

    /**
     * A end array.
     */
    END_ARRAY,

    /**
     * True value.
     */
    TRUE,

    /**
     * False value.
     */
    FALSE,

    /**
     * The name token.
     */
    NAME,

    /**
     * The num token.
     */
    NUM,

    /**
     * The string token.
     */
    STRING,

    /**
     * The percent token.
     */
    PERCENT,

    /**
     * The token to start a dictionary.
     */
    START_DICT,

    /**
     * The token to end a dictionary.
     */
    END_DICT,

    /**
     * The new line token.
     */
    NEW_LINE,

    /**
     * The object token.
     */
    OBJ,

    /**
     * Indicates a end of object.
     */
    END_OBJ,

    /**
     * Indicates the end of PDF file.
     */
    END_PDF,

    /**
     * The XREF token.
     */
    XREF,

    /**
     * The trailer token.
     */
    TRAILER,

    /**
     * The start XREF token.
     */
    START_XREF,

    /**
     * The stream token.
     */
    STREAM,

    /**
     * Indicates the end of stream.
     */
    END_STREAM,

    /**
     * The WLO token.
     */
    W_LO,

    /**
     * The JLO token.
     */
    J_LO,

    /**
     * The JUP token.
     */
    J_UP,

    /**
     * The MUP token.
     */
    M_UP,

    /**
     * The D token.
     */
    D,

    /**
     * The RI token.
     */
    RI,

    /**
     * The I token.
     */
    I,

    /**
     * The GS token.
     */
    GS,

    /**
     * The SUP token.
     */
    S_UP,

    /**
     * The SLO token.
     */
    S_LO,

    /**
     * The FUP token.
     */
    F_UP,

    /**
     * The FLO token.
     */
    F_LO,

    /**
     * The FAST token.
     */
    F_AST,

    /**
     * The BUP token.
     */
    B_UP,

    /**
     * The BUPAST token.
     */
    B_UP_AST,

    /**
     * The BLO token.
     */
    B_LO,

    /**
     * The BLOAST token.
     */
    B_LO_AST,

    /**
     * the N token.
     */
    N,

    /**
     * The QUP token.
     */
    Q_UP,

    /**
     * The QLO token.
     */
    Q_LO,

    /**
     * The CM token.
     */
    CM,

    /**
     * The V token.
     */
    V,

    /**
     * The Y token.
     */
    Y,

    /**
     * The MLO token.
     */
    M_LO,

    /**
     * The L token.
     */
    L,

    /**
     * The C token.
     */
    C,

    /**
     * The H token.
     */
    H, RE,

    /**
     * The WAST token.
     */
    W_AST,

    /**
     * The WUP token.
     */
    W_UP,

    /**
     * The BT token.
     */
    BT,

    /**
     * The ET token.
     */
    ET,

    /**
     * The TC token.
     */
    TC,

    /**
     * The TW token.
     */
    TW,

    /**
     * The TZ token.
     */
    TZ,

    /**
     * The TL token.
     */
    TL,

    /**
     * The TF token.
     */
    TF,

    /**
     * The TR token.
     */
    TR,

    /**
     * The TS token.
     */
    TS,

    /**
     * The TDUP token.
     */
    TD_UP,

    /**
     * The TDLO token.
     */
    TD_LO,

    /**
     * The TM token.
     */
    TM,

    /**
     * The TAST token.
     */
    T_AST,

    /**
     * The TJUP token.
     */
    TJ_UP,

    /**
     * The TJLO token.
     */
    TJ_LO,

    /**
     * The quote token.
     */
    QUOTE,

    /**
     * The double quote token.
     */
    DOUBLE_QUOTE,

    /**
     * The D0 token.
     */
    D0,

    /**
     * The D1 token.
     */
    D1,

    /**
     * The CSUP token.
     */
    CS_UP,

    /**
     * The CSLO token.
     */
    CS_LO,

    /**
     * The SCNUP token.
     */
    SCN_UP,

    /**
     * The SCNLO token.
     */
    SCN_LO,

    /**
     * The SCUP token.
     */
    SC_UP,

    /**
     * The SCLO token.
     */
    SC_LO,

    /**
     * The GLO token.
     */
    G_LO,

    /**
     * The GUP token.
     */
    G_UP,

    /**
     * The RGLO token.
     */
    RG_LO,

    /**
     * The RGUP token.
     */
    RG_UP,

    /**
     * The KLO token.
     */
    K_LO,

    /**
     * The KUP token.
     */
    K_UP,

    /**
     * The SH token.
     */
    SH,

    /**
     * The BI token.
     */
    BI,

    /**
     * The ID token.
     */
    ID,

    /**
     * The EI token.
     */
    EI,

    /**
     * The XObject token.
     */
    DO,

    /**
     * The MP token.
     */
    MP,

    /**
     * The DP token.
     */
    DP,

    /**
     * The BMC token.
     */
    BMC,

    /**
     * The BDC token.
     */
    BDC,

    /**
     * The EMC token.
     */
    EMC,

    /**
     * The BX token.
     */
    BX,

    /**
     * The EX token.
     */
    EX
};

/**
 * Stores a single token.
 */
class Token
{
private:
    /**
     * The token type.
     */
    TokenType m_type = TokenType::ENDFILE;

    /**
     * the token value.
     */
    std::string m_value;

public:
    /**
     * Creates a new instance.
     */
    Token() = default;

    /**
     * Destroy this instance.
     */
    ~Token() = default;

    /**
     * Sets the token value.
     *
     * @param value the token value.
     */
    void setValue(std::string value);

    /**
     * Sets the token type.
     *
     * @param type the token type.
     */
    void setType(TokenType type);

    /**
     * Converts the token value to number.
     *
     * @return the number value.
     */
    double toNumber() const;
    
    
    /**
     * Converts the value to int.
     *
     * @return the int value.
     */
    int ToInt() const;

    /**
     * Gets the token value.
     *
     * @return the token value.
     */
    std::string value() const;

    /**
     * Gets the token type.
     *
     * @return the token type.
     */
    TokenType type() const;
};
}

#endif
