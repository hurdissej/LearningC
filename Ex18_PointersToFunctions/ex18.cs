using system;
using System.Linq;

public static class Program
{
    public static int main(string[] args)
    {
        args.Select(x => int.Parse(x)).OrderBy(x => x);
    }
}