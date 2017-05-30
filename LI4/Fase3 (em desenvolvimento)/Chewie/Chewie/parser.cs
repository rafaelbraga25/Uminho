using System.Collections.Generic;
using System.Text.RegularExpressions;
using System;

class Parser
{
    private readonly string[] POSITIVE = { "com", ",", ":", "mais" };
    private readonly string[] NEGATIVE = { "sem", "menos", "exceto" }; 


    private bool compareValue(string str, string[] list)
    {
        bool value = false;

        foreach (string s in list)
        {
            if (s.CompareTo(str) == 0)
            {
                value = true;
                break;
            }
        }

        return value;
    }


    private string getPattern()
    {
        string p = "(";

        foreach (string s in POSITIVE)
        {
            p += s + "|";
        }

        foreach (string s in NEGATIVE)
        {
            p += s + "|";
        }

        p = p.Remove(p.Length - 1, 1) + ")";

        return p;
    }


    private string removeWhiteSpaces(string str)
    {
        Regex rgx = new Regex("[\\s\\t\\n]+");

        str = rgx.Replace(str, " ");
        rgx = new Regex("^[\\s\\n\\t]+");

        str = rgx.Replace(str, "");
        rgx = new Regex("[\\s\\n\\t]+$");

        str = rgx.Replace(str, "");

        return str;
    }


    private DishDetails getDishDetails(string str)
    {
        DishDetails d = new DishDetails();
        string detail = "";
        bool value = false;
        bool auxValue = false;

        string pattern = getPattern();

        List<string> fields = new List<string>(Regex.Split(str, pattern));

        d.setDish(removeWhiteSpaces(fields[0]));
        fields.RemoveAt(0);

        foreach (string s in fields)
        {
            if (compareValue(s, POSITIVE) == true)
            {
                value = true;
                continue;
            }
            else if (compareValue(s, NEGATIVE) == true)
            {
                value = false;
                continue;
            }

            detail = removeWhiteSpaces(s);

            if (detail.CompareTo("") != 0)
            {
                try
                {
                    auxValue = d.getValue(detail);

                    if (auxValue != value)
                    {
                        d.removeDetail(detail);
                    }
                }
                catch (KeyNotFoundException)
                {
                    d.addDetail(detail, value);
                }
            }
        }

        return d;
    }


    public DishDetails parse(string str)
    {
        return getDishDetails(removeWhiteSpaces(str.ToLower()));
    }
}
