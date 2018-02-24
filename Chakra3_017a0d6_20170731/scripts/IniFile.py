import re
import string

class _KeyValue(dict):
    def __init__(self, parent):
        self.parent = parent

    def __getitem__(self, key):
        if key not in self:
            dict.__setitem__(self, key, '')
        return dict.__getitem__(self, key)

    def __setitem__(self, key, value):
        if self[key] != value:
            self.parent.dirty = True
            dict.__setitem__(self, key, value)

class IniFile(dict):
    _section = re.compile(r'^\[(.*)\]\s*')
    _option  = re.compile(r'^([^=\s]*)\s*=\s*(.*)$')

    def __init__(self, fn, norm=1):
        """if norm=0, won't convert section/options's case"""
        dict.__init__(self)
        self.filename = fn
        self.normalize = norm

        try:
            # Parse the .ini file
            f = open(fn, 'r+')
            sect = ''
            for line in f:
                line = string.strip(line)
                if line == '' or line[0] == ';' or line[0] == '#':
                    continue
                m = self._section.match(line)
                if m != None:
                    sect = m.group(1)
                elif sect:
                    m = self._option.match(line)
                    if m != None:
                        opt, val = m.group(1, 2)
                        dict.__setitem__(self[sect], opt, val)
            f.close()
            del f
        except IOError, e:
            #print e
            pass
        self.dirty = False

    def __getitem__(self, sect):
        if self.normalize:
            sect = sect.upper()
        if sect not in self:
            dict.__setitem__(self, sect, _KeyValue(self))
        return dict.__getitem__(self, sect)

    def write(self):
        """Write an .ini-format representation of the configuration state."""
        try:
            f = open(self.filename,'w')
            for section in self.keys():
                f.write('[%s]\n' % section)
                for (key, value) in self.__getitem__(section).items():
                    f.write('%s=%s\n' % (key, str(value)))
            f.close()
            del f
            self.dirty = False
        except IOError, e:
            print e

if __name__ == '__main__':
    ini = IniFile('PyTV_Tool.ini')
    ini['SECTION']['KEY'] = 'value'
    ini.write()
    del ini