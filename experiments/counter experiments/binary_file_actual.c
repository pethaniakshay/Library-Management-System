

int main()
{
    FILE *fp;
    int aaa,temp;
    sc.civil=0;
    sc.cs=0;
    sc.ec=0;
    sc.ee=0;
    sc.ic=0;
    sc.mech=0;
    system("cls");



        fp=fopen("student_counter.dat","ab+");
        fread(&sc,sizeof(sc),1,fp);
        temp=sc.civil;
        fclose(fp);

        fp=fopen("student_counter.dat","rb+");
        if(temp>100)
        {
            sc.civil++;
        }
        else
        {
            sc.civil=100;
            sc.civil++;
        }

        fseek(fp,ftell(fp)-sizeof(sc),0);
        fwrite(&sc,sizeof(sc),1,fp);
        fclose(fp);
        return sc.civil;
}
