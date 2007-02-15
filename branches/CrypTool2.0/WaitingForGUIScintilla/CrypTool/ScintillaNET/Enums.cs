using System;
using System.Windows.Forms;


namespace Scintilla.Enums
{
	#region "scintilla-enums"
    public enum WhiteSpace
    {    
        invisible = 0,
        visiblealways = 1,
        visibleafterindent = 2
    }
    public enum EndOfLine
    {    
        crlf = 0,
        cr = 1,
        lf = 2
    }
    public enum MarkerSymbol
    {    
        circle = 0,
        roundrect = 1,
        arrow = 2,
        smallrect = 3,
        shortarrow = 4,
        empty = 5,
        arrowdown = 6,
        minus = 7,
        plus = 8,
        vline = 9,
        lcorner = 10,
        tcorner = 11,
        boxplus = 12,
        boxplusconnected = 13,
        boxminus = 14,
        boxminusconnected = 15,
        lcornercurve = 16,
        tcornercurve = 17,
        circleplus = 18,
        circleplusconnected = 19,
        circleminus = 20,
        circleminusconnected = 21,
        background = 22,
        dotdotdot = 23,
        arrows = 24,
        pixmap = 25,
        character = 10000
    }
    public enum MarkerOutline
    {    
        folderend = 25,
        folderopenmid = 26,
        foldermidtail = 27,
        foldertail = 28,
        foldersub = 29,
        folder = 30,
        folderopen = 31
    }
    public enum MarginType
    {    
        symbol = 0,
        number = 1
    }
    public enum StylesCommon
    {    
        @default = 32,
        linenumber = 33,
        bracelight = 34,
        bracebad = 35,
        controlchar = 36,
        indentguide = 37,
        lastpredefined = 39,
        max = 127
    }
    public enum CharacterSet
    {    
        ansi = 0,
        @default = 1,
        baltic = 186,
        chinesebig5 = 136,
        easteurope = 238,
        gb2312 = 134,
        greek = 161,
        hangul = 129,
        mac = 77,
        oem = 255,
        russian = 204,
        shiftjis = 128,
        symbol = 2,
        turkish = 162,
        johab = 130,
        hebrew = 177,
        arabic = 178,
        vietnamese = 163,
        thai = 222
    }
    public enum CaseVisible
    {    
        mixed = 0,
        upper = 1,
        lower = 2
    }
    public enum IndicatorStyle
    {    
        max = 7,
        plain = 0,
        squiggle = 1,
        tt = 2,
        diagonal = 3,
        strike = 4,
        hidden = 5,
        box = 6
    }
    public enum PrintOption
    {    
        normal = 0,
        invertlight = 1,
        blackonwhite = 2,
        colouronwhite = 3,
        colouronwhitedefaultbg = 4
    }
    public enum FindOption
    {    
        wholeword = 2,
        matchcase = 4,
        wordstart = 0x00100000,
        regexp = 0x00200000,
        posix = 0x00400000
    }
    public enum FoldLevel
    {    
        @base = 0x400,
        whiteflag = 0x1000,
        headerflag = 0x2000,
        boxheaderflag = 0x4000,
        boxfooterflag = 0x8000,
        contracted = 0x10000,
        unindent = 0x20000,
        numbermask = 0x0FFF
    }
    public enum FoldFlag
    {    
        linebefore_expanded = 0x0002,
        linebefore_contracted = 0x0004,
        lineafter_expanded = 0x0008,
        lineafter_contracted = 0x0010,
        levelnumbers = 0x0040,
        box = 0x0001
    }
    public enum Wrap
    {    
        none = 0,
        word = 1
    }
    public enum WrapVisualFlag
    {    
        none = 0x0000,
        end = 0x0001,
        start = 0x0002
    }
    public enum WrapVisualLocation
    {    
        @default = 0x0000,
        end_by_text = 0x0001,
        start_by_text = 0x0002
    }
    public enum LineCache
    {    
        none = 0,
        caret = 1,
        page = 2,
        document = 3
    }
    public enum EdgeVisualStyle
    {    
        none = 0,
        line = 1,
        background = 2
    }
    public enum CursorShape
    {    
        normal = -1,
        wait = 4
    }
    public enum CaretPolicy
    {    
        slop = 0x01,
        strict = 0x04,
        jumps = 0x10,
        even = 0x08
    }
    public enum SelectionMode
    {    
        stream = 0,
        rectangle = 1,
        lines = 2
    }
    public enum ModificationFlags
    {    
        inserttext = 0x1,
        deletetext = 0x2,
        changestyle = 0x4,
        changefold = 0x8,
        user = 0x10,
        undo = 0x20,
        redo = 0x40,
        stepinundoredo = 0x100,
        changemarker = 0x200,
        beforeinsert = 0x400,
        beforedelete = 0x800
    }
    public enum Keys
    {    
        down = 300,
        up = 301,
        left = 302,
        right = 303,
        home = 304,
        end = 305,
        prior = 306,
        next = 307,
        delete = 308,
        insert = 309,
        escape = 7,
        back = 8,
        tab = 9,
        @return = 13,
        add = 310,
        subtract = 311,
        divide = 312
    }
    public enum KeyMod
    {    
        shift = 1,
        ctrl = 2,
        alt = 4
    }
    public enum Lexer
    {    
        container = 0,
        @null = 1,
        python = 2,
        cpp = 3,
        html = 4,
        xml = 5,
        perl = 6,
        sql = 7,
        vb = 8,
        properties = 9,
        errorlist = 10,
        makefile = 11,
        batch = 12,
        xcode = 13,
        latex = 14,
        lua = 15,
        diff = 16,
        conf = 17,
        pascal = 18,
        ave = 19,
        ada = 20,
        lisp = 21,
        ruby = 22,
        eiffel = 23,
        eiffelkw = 24,
        tcl = 25,
        nncrontab = 26,
        bullant = 27,
        vbscript = 28,
        asp = 29,
        php = 30,
        baan = 31,
        matlab = 32,
        scriptol = 33,
        asm = 34,
        cppnocase = 35,
        fortran = 36,
        f77 = 37,
        css = 38,
        pov = 39,
        lout = 40,
        escript = 41,
        ps = 42,
        nsis = 43,
        mmixal = 44,
        clw = 45,
        clwnocase = 46,
        lot = 47,
        yaml = 48,
        tex = 49,
        metapost = 50,
        powerbasic = 51,
        forth = 52,
        erlang = 53,
        octave = 54,
        mssql = 55,
        verilog = 56,
        kix = 57,
        gui4cli = 58,
        specman = 59,
        au3 = 60,
        apdl = 61,
        bash = 62,
        automatic = 1000
    }
	#endregion

}
