#ifndef _SYMBOLSOURCEBASE_H_
#define _SYMBOLSOURCEBASE_H_

#include "_global.h"

#include <stdint.h>
#include <vector>
#include <functional>

struct SymbolInfo
{
    duint addr;
    duint size;
    int32 disp;
    String decoratedName;
    String undecoratedName;
    bool valid;
};

using CbEnumSymbol = std::function<bool(const SymbolInfo &)>;

class SymbolSourceBase
{
private:
    std::vector<uint8_t> _symbolBitmap;

public:
    virtual ~SymbolSourceBase() = default;

    void resizeSymbolBitmap(size_t imageSize)
    {
        if(!isOpen())
            return;

        _symbolBitmap.resize(imageSize);
        std::fill(_symbolBitmap.begin(), _symbolBitmap.end(), false);
    }

    void markAdressInvalid(duint rva)
    {
        if(_symbolBitmap.empty())
            return;

        _symbolBitmap[rva] = true;
    }

    bool isAddressInvalid(duint rva) const
    {
        if(_symbolBitmap.empty())
            return false;

        return !!_symbolBitmap[rva];
    }

    // Tells us if the symbols are loaded for this module.
    virtual bool isOpen() const
    {
        return false; // Stub
    }

    virtual bool isLoading() const
    {
        return false; // Stub
    }

    // Get the symbol at the specified address, will return false if not found.
    virtual bool findSymbolExact(duint rva, SymbolInfo & symInfo)
    {
        return false; // Stub
    }

    // Get the symbol at the address or the closest behind, in case it got the closest it will set disp to non-zero, false on nothing.
    virtual bool findSymbolExactOrLower(duint rva, SymbolInfo & symInfo)
    {
        return false; // Stub
    }

    virtual void enumSymbols(const CbEnumSymbol & cbEnum)
    {
        // Stub
    }
};

static SymbolSourceBase EmptySymbolSource;

#endif // _SYMBOLSOURCEBASE_H_