
class Regex {
public:
    bool isEqual(char a, char b) {
      return (a==b || b=='.');
    }

    bool isMatch(const char *s, const char *p) {
        while (*s != '\0' && *p != '\0' && *(p+1) != '*') {
            if (!isEqual(*s, *p))
              return false;
            ++s; ++p;
        }
        if (*p == '\0')
          return (*s == '\0'); // p finishes first.
        if (*s == '\0' && *(p+1) != '*')
          return false; // s finishes first
        while (*s != '\0' && isEqual(*s ,*p)) {
          if (isMatch(s, p+2))
            return true;
          ++s;
        }
        return isMatch(s, p+2);
    }
};
