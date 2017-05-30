using System.Collections.Generic;


class DishDetails
{
    private string dish;
    private Dictionary<string, bool> details;


    public DishDetails()
    {
        dish = "";
        details = new Dictionary<string, bool>();
    }


    public DishDetails(string dish, Dictionary<string, bool> details)
    {
        this.dish = dish;
        this.details = details;
    }


    public DishDetails(DishDetails d)
    {
        this.dish = d.getDish();
        this.details = d.getDetails();
    }


    public string getDish()
    {
        return dish;
    }


    public Dictionary<string, bool> getDetails()
    {
        return details;
    }


    public void setDish(string dish)
    {
        this.dish = dish;
    }


    public void setDetails(Dictionary<string, bool> details)
    {
        this.details = details;
    }


    public void addDetail(string detail, bool value)
    {
        details.Add(detail, value);
    }


    public bool getValue(string detail)
    {
        bool value = false;

        try
        {
            value = details[detail];
        }
        catch (KeyNotFoundException e)
        {
            throw e;
        }

        return value;
    }


    public void removeDetail(string detail)
    {
        details.Remove(detail);
    }


    public DishDetails clone()
    {
        return new DishDetails(this);
    }
}