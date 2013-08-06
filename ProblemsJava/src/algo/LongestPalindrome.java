package algo;

public class LongestPalindrome {
  String expand(String s, int left, int right)
  {
    boolean hasPal = false;
    while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right))
    {
      hasPal = true;
      --left;
      ++right;
    }
    return (hasPal ? s.substring(left + 1, right) : null);
  }

  public String longestPalindrome(String s)
  {
    if (s.length() == 0)
      return "";
    String longestPal = s.substring(0, 1);
    for (int i = 0; i < s.length(); ++i)
    {
      String pal = expand(s, i, i + 1);
      if (pal != null && pal.length() > longestPal.length())
        longestPal = pal;
      pal = expand(s, i, i + 2);
      if (pal != null && pal.length() > longestPal.length())
        longestPal = pal;
    }
    return longestPal;
  }

}
