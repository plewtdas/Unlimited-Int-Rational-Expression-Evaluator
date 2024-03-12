/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"

// #include <iostream>

UnlimitedInt::UnlimitedInt() {}

UnlimitedInt::UnlimitedInt(string s)
{
    if (s[0] == '-')
    {
        sign = -1;
        size = s.length() - 1;
        capacity = size;
        int *arr = new int[capacity];
        for (int j = 1; j < capacity + 1; j++)
        {
            arr[j - 1] = int(s[j]) - 48;
        }
        unlimited_int = arr;
    }
    else
    {
        sign = 1;
        size = s.length();
        capacity = size;
        int *arr = new int[capacity];
        for (int j = 0; j < capacity; j++)
        {
            arr[j] = int(s[j]) - 48;
        }
        unlimited_int = arr;
    }
}

UnlimitedInt::UnlimitedInt(int i)
{
    if (i < 0)
    {
        sign = -1;
        i = i * (-1);
    }
    else
    {
        sign = 1;
    }
    int p = 0;
    int k = i;

    if (k == 0)
    {
        size = 1;
        int t = i;
        capacity = size;
        int *arr = new int[capacity];
        for (int j = capacity - 1; j > -1; j--)
        {
            arr[j] = t % 10;
            t = t / 10;
        }
        // cout<<"hi1";
        unlimited_int = arr;
        return;
    }

    while (k != 0)
    {
        p += 1;
        k = k / 10;
    }

    int t = i;
    size = p;
    capacity = size;
    int *arr = new int[capacity];

    for (int j = capacity - 1; j > -1; j--)
    {
        arr[j] = t % 10;
        t = t / 10;
    }
    // cout<<"hi1";
    unlimited_int = arr;
}

UnlimitedInt::UnlimitedInt(int *ulimited_int, int cap, int sgn, int sz)
{
    unlimited_int = ulimited_int;
    capacity = cap;
    sign = sgn;
    size = sz;
}

UnlimitedInt::~UnlimitedInt()
{
    delete [] unlimited_int;
}

int UnlimitedInt::get_sign()
{
    return sign;
}

int UnlimitedInt::get_size()
{
    return size;
}

int UnlimitedInt::get_capacity()
{
    return capacity;
}

int *UnlimitedInt::get_array()
{
    return unlimited_int;
}

UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int s1 = i1->get_sign();
    int s2 = i2->get_sign();

    if (s1 * s2 >= 0)
    {
        int p1 = i1->get_size();
        int p2 = i2->get_size();
        int *arr1 = i1->get_array();
        int *arr2 = i2->get_array();
        int *ar = new int[max(p1, p2)];
        if (p1 < p2)
        {
            for (int j = 0; j < p2 - p1; j++)
            {
                ar[j] = 0;
            }
            int p = 0;
            int j = p2 - p1;
            while (p < p1)
            {
                ar[j] = arr1[p];
                j += 1;
                p += 1;
            }

            int m = max(p1, p2);
            int c = m - 1;
            int carry = 0;

            int *obj = new int[m];

            while (c > -1)
            {
                int num = (arr2[c] + ar[c] + carry) % 10;
                carry = ((arr2[c] + ar[c] + carry) / 10);
                // cout << "carry: " << carry << endl;
                obj[c] = num;
                c -= 1;
            }
            delete[] ar;
            UnlimitedInt *object = new UnlimitedInt;
            // cout<<m<<" " <<s1<<endl;
            object->size = m;
            object->capacity = m;
            object->sign = s1;
            object->unlimited_int = obj;
            if (carry != 0)
            {
                int *objj = new int[m + 1];
                int g = m;
                while (g > 0)
                {
                    objj[g] = obj[g - 1];
                    // cout << "ob:" << objj[g] << endl;
                    g -= 1;
                }
                objj[0] = carry;
                delete[] obj;
                m += 1;
                object->size = m;
                object->capacity = m;
                object->sign = s1;
                object->unlimited_int = objj;
            }

            return object;
        }
        else
        {
            for (int j = 0; j < p1 - p2; j++)
            {
                ar[j] = 0;
            }
            int p = 0;
            int j = p1 - p2;
            while (p < p2)
            {
                ar[j] = arr2[p];
                j += 1;
                p += 1;
            }

            int m = max(p1, p2);
            int c = m - 1;
            int carry = 0;

            int *obj = new int[m];

            while (c > -1)
            {
                int num = (arr1[c] + ar[c] + carry) % 10;
                carry = ((arr1[c] + ar[c] + carry) / 10);
                // cout << "carry: " << carry << endl;
                obj[c] = num;
                c -= 1;
            }
            
            UnlimitedInt *object = new UnlimitedInt;
            // cout<<m<<" " <<s1<<endl;
            object->size = m;
            object->capacity = m;
            object->sign = s1;
            object->unlimited_int = obj;
            if (carry != 0)
            {
                int *objj = new int[m + 1];
                int g = m;
                while (g > 0)
                {
                    objj[g] = obj[g - 1];
                    // cout << "ob:" << objj[g] << endl;
                    g -= 1;
                }
                objj[0] = carry;
                delete[] obj;
                m += 1;
                object->size = m;
                object->capacity = m;
                object->sign = s1;
                object->unlimited_int = objj;
            }

            return object;
        }
    }
    else
    {
        int p1 = i1->get_size();
        int p2 = i2->get_size();
        int *arr1 = i1->get_array();
        int *arr2 = i2->get_array();

        if (s1 < 0)
        {
            UnlimitedInt *object = new UnlimitedInt;
            object->size = p1;
            object->sign = 1;
            object->unlimited_int = arr1;
            object->capacity = p1;
            return sub(i2, object);
        }
        else
        {
            UnlimitedInt *object = new UnlimitedInt;
            object->size = p2;
            object->sign = 1;
            object->unlimited_int = arr2;
            object->capacity = p1;
            return sub(i1, object);
        }
    }
}

UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int s1 = i1->get_sign();
    int s2 = i2->get_sign();
    if (s1 * s2 > 0)
    {
        int p1 = i1->get_size();
        int p2 = i2->get_size();
        int *arr1 = i1->get_array();
        int *arr2 = i2->get_array();
        bool magnitudeone = true; // magnitude 1 is bigger
        if (p2 > p1)
        {
            magnitudeone = false;
        }
        else if (p1 == p2)
        {
            for (int j = 0; j < p1; j++)
            {
                if (arr2[j] > arr1[j])
                {
                    magnitudeone = false;
                    break;
                }
                else if (arr1[j] > arr2[j])
                {
                    break;
                }
            }
        }
        // cout<<magnitudeone<<endl;
        UnlimitedInt *object = new UnlimitedInt;
        if (magnitudeone)
        {
            int *ar = new int[max(p1, p2)];
            for (int j = 0; j < p1 - p2; j++)
            {
                ar[j] = 0;
            }
            int p = 0;
            int j = p1 - p2;
            while (p < p2)
            {
                ar[j] = arr2[p];
                j += 1;
                p += 1;
            }
            int m = max(p1, p2);
            int c = m - 1;
            int borrow = 0;

            int *obj = new int[m];

            while (c > -1)
            {
                int num = (arr1[c] - ar[c] - borrow);
                if (num < 0)
                {
                    num += 10;
                    borrow = 1;
                }
                else
                {
                    borrow = 0;
                }
                obj[c] = num;
                c -= 1;
                // cout << "borrow: " << borrow << endl;
            }
            delete[] ar;

            int y = 0;
            while (y < m and obj[y] == 0)
            {
                y += 1;
            }
            int sz = m - y;
            if (sz == 0)
            {
                delete[] obj;
                object->size = 1;
                object->capacity = 1;
                object->sign = 1;
                int *objj = new int[sz];
                objj[0] = 0;
                object->unlimited_int = objj;
                return object;
            }
            int *objj = new int[sz];
            int d = 0;
            while (y < m)
            {
                objj[d] = obj[y];
                y += 1;
                d += 1;
            }
            delete[] obj;

            // cout<<m<<" " <<s1<<endl;
            object->size = sz;
            object->capacity = sz;
            object->sign = s1;
            object->unlimited_int = objj;
        }
        else
        {
            int *ar = new int[max(p1, p2)];
            for (int j = 0; j < p2 - p1; j++)
            {
                ar[j] = 0;
            }
            int p = 0;
            int j = p2 - p1;
            while (p < p1)
            {
                ar[j] = arr1[p];
                j += 1;
                p += 1;
            }
            int m = max(p1, p2);
            int c = m - 1;
            int borrow = 0;

            int *obj = new int[m];

            while (c > -1)
            {
                int num = (arr2[c] - ar[c] - borrow);
                if (num < 0)
                {
                    num += 10;
                    borrow = 1;
                }
                else
                {
                    borrow = 0;
                }
                obj[c] = num;
                c -= 1;
                // cout << "borrow: " << borrow << endl;
            }
            delete[] ar;

            int y = 0;
            while (y < m and obj[y] == 0)
            {
                y += 1;
            }
            int sz = m - y;
            if (sz == 0)
            {
                delete[] obj;
                object->size = 1;
                object->capacity = 1;
                object->sign = 1;
                int *objj = new int[sz];
                objj[0] = 0;
                object->unlimited_int = objj;
                return object;
            }
            int *objj = new int[sz];
            int d = 0;
            while (y < m)
            {
                objj[d] = obj[y];
                y += 1;
                d += 1;
            }
            delete[] obj;
            // int *objj = new int[sz];
            // cout<<m<<" " <<s1<<endl;
            object->size = sz;
            object->capacity = sz;
            object->sign = s1 * (-1);
            object->unlimited_int = objj;
        }

        return object;
    }
    else
    {
        int p1 = i1->get_size();
        int p2 = i2->get_size();
        int *arr1 = i1->get_array();
        int *arr2 = i2->get_array();
        if (s1 < 0)
        {
            UnlimitedInt *object1 = new UnlimitedInt;
            object1->size = p1;
            object1->sign = -1;
            object1->unlimited_int = arr1;
            object1->capacity = p1;
            UnlimitedInt *object2 = new UnlimitedInt;
            object2->size = p2;
            object2->sign = -1;
            object2->unlimited_int = arr2;
            object2->capacity = p2;
            return add(object1, object2);
        }
        else
        {
            UnlimitedInt *object1 = new UnlimitedInt;
            object1->size = p1;
            object1->sign = 1;
            object1->unlimited_int = arr1;
            object1->capacity = p1;
            UnlimitedInt *object2 = new UnlimitedInt;
            object2->size = p2;
            object2->sign = 1;
            object2->unlimited_int = arr2;
            object2->capacity = p2;
            return add(object1, object2);
        }
    }
}

UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{

    UnlimitedInt *objectans = new UnlimitedInt;
    objectans->size = 1;
    objectans->capacity = 1;
    objectans->sign = 1;
    int *ans = new int[1];
    ans[0] = 0;
    objectans->unlimited_int = ans;

    int s1 = i1->get_sign();
    int s2 = i2->get_sign();
    // int p1 = i1->get_size();
    int p2 = i2->get_size();
    // int *arr1 = i1->get_array();
    int *arr2 = i2->get_array();
    string str1 = i1->to_string();
    string str2 = i2->to_string();
    if (str1 == "0")
    {
        return objectans;
    }

    for (int j = p2 - 1; j > -1; j--)
    {
        UnlimitedInt *object = new UnlimitedInt;
        object->size = 1;
        object->capacity = 1;
        object->sign = 1;
        int *ar = new int[1];
        ar[0] = 0;
        object->unlimited_int = ar;
        // UnlimitedInt *temp=new UnlimitedInt;
        for (int p = 0; p < arr2[j]; p++)
        {
            UnlimitedInt *temp = new UnlimitedInt;
            temp = add(object, i1);
            delete object;
            object = temp;
        }

        int b = object->get_size();
        int *tr = object->get_array();
        int *array = new int[b + p2 - j - 1];
        for (int t = 0; t < b; t++)
        {
            array[t] = tr[t];
        }
        for (int t = b; t < b + p2 - j - 1; t++)
        {
            array[t] = 0;
        }

        object->unlimited_int = array;
        object->size = b + p2 - j - 1;
        object->capacity = b + p2 - j - 1;

        UnlimitedInt *temp = new UnlimitedInt;
        temp = add(objectans, object);
        delete objectans;
        delete object;
        objectans = temp;
    }
    if (s1 * s2 > 0)
    {
        objectans->sign = 1;
    }
    else
    {
        objectans->sign = -1;
        if (str1 == "0" or str2 == "0")
        {
            objectans->sign = 1;
        }
    }
    return objectans;
}

UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int s1 = i1->get_sign();
    int s2 = i2->get_sign();
    int p1 = i1->get_size();
    int p2 = i2->get_size();
    int *arr1 = i1->get_array();
    int *arr2 = i2->get_array();
    if (p2 == 1 and arr2[0] == 0)
    {
        UnlimitedInt *object = new UnlimitedInt;
        object->size = 1;
        object->capacity = 1;
        object->sign = 1;
        int *ar = new int[1];
        ar[0] = 0;
        object->unlimited_int = ar;
        return object;
    }
    if (p1 == 1 and arr1[0] == 0)
    {
        UnlimitedInt *object = new UnlimitedInt;
        object->size = 1;
        object->capacity = 1;
        object->sign = 1;
        int *ar = new int[1];
        ar[0] = 0;
        object->unlimited_int = ar;
        return object;
    }
    if (s1 < 0 and s2 < 0)
    {
        UnlimitedInt *object11 = new UnlimitedInt;
        object11->size = i1->size;
        object11->capacity = i1->capacity;
        object11->sign = 1;
        object11->unlimited_int = i1->unlimited_int;

        UnlimitedInt *object12 = new UnlimitedInt;
        object12->size = i2->size;
        object12->capacity = i2->capacity;
        object12->sign = 1;
        object12->unlimited_int = i2->unlimited_int;

        return div(object11, object12);
    }
    if (s1 < 0 and s2 > 0)
    {
        UnlimitedInt *object11 = new UnlimitedInt;
        object11->size = i1->size;
        object11->capacity = i1->capacity;
        object11->sign = 1;
        object11->unlimited_int = i1->unlimited_int;

        UnlimitedInt *object12 = div(object11, i2);
        object12->sign = -1;

        UnlimitedInt *objmod = mod(object11, i2);
        // delete object11;
        int aq = objmod->size;
        int *arw = objmod->unlimited_int;
        if (aq == 1 and arw[0] == 0)
        {
            return object12;
        }

        UnlimitedInt *object13 = new UnlimitedInt;
        object13->size = 1;
        object13->capacity = 1;
        object13->sign = -1;
        int *ar = new int[1];
        ar[0] = 1;
        object13->unlimited_int = ar;
        UnlimitedInt *object14 = add(object12, object13);
        delete object12;
        delete object13;
        return object14;
    }
    if (s1 > 0 and s2 < 0)
    {
        UnlimitedInt *object11 = new UnlimitedInt;
        object11->size = i2->size;
        object11->capacity = i2->capacity;
        object11->sign = 1;
        object11->unlimited_int = i2->unlimited_int;

        UnlimitedInt *object12 = div(i1, object11);
        object12->sign = -1;

        UnlimitedInt *objmod = mod(i1, object11);
        // delete object11;
        int aq = objmod->size;
        int *arw = objmod->unlimited_int;
        if (aq == 1 and arw[0] == 0)
        {
            return object12;
        }

        UnlimitedInt *object13 = new UnlimitedInt;
        object13->size = 1;
        object13->capacity = 1;
        object13->sign = -1;
        int *ar = new int[1];
        ar[0] = 1;
        object13->unlimited_int = ar;
        UnlimitedInt *object14 = add(object12, object13);
        delete object12;
        delete object13;
        return object14;
    }

    bool magnitudeone = true; // magnitude 1 is bigger
    if (p2 > p1)
    {
        magnitudeone = false;
    }
    else if (p1 == p2)
    {
        for (int j = 0; j < p1; j++)
        {
            if (arr2[j] > arr1[j])
            {
                magnitudeone = false;
                break;
            }
            else if (arr1[j] > arr2[j])
            {
                break;
            }
        }
    }

    if (magnitudeone == false)
    {
        UnlimitedInt *object = new UnlimitedInt;
        object->size = 1;
        object->capacity = 1;
        object->sign = 1;
        int *ar = new int[1];
        ar[0] = 0;
        object->unlimited_int = ar;
        return object;
    }
    UnlimitedInt *object = new UnlimitedInt;
    object->size = i1->size;
    object->capacity = i1->capacity;
    object->sign = i1->sign;
    object->unlimited_int = i1->unlimited_int;

    UnlimitedInt *objectadd = new UnlimitedInt;
    objectadd->size = 1;
    objectadd->capacity = 1;
    objectadd->sign = 1;
    int *ar = new int[1];
    ar[0] = 0;
    objectadd->unlimited_int = ar;

    while (magnitudeone)
    {
        bool nexttaken = false;
        string s = "";
        int number = 0;
        int g1 = object->size;
        int *grr1 = object->get_array();
        if (p2 > g1)
        {
            magnitudeone = false;
        }
        else if (g1 == p2)
        {
            for (int j = 0; j < g1; j++)
            {
                if (arr2[j] > grr1[j])
                {
                    magnitudeone = false;
                    break;
                }
                else if (grr1[j] > arr2[j])
                {
                    break;
                }
            }
        }
        if (magnitudeone == false)
        {
            break;
        }

        UnlimitedInt *objecthelp = new UnlimitedInt;
        objecthelp->size = p2;
        objecthelp->capacity = p2;
        objecthelp->sign = s1;
        int *arhelp = new int[p2];
        for (int j = 0; j < p2; j++)
        {
            arhelp[j] = grr1[j];
            // cout<<"helpergrr: "<<grr1[j];
        }
        // cout<<endl;
        objecthelp->unlimited_int = arhelp;

        UnlimitedInt *objectsub = sub(objecthelp, i2);
        // cout<<"sign"<<objectsub->get_sign();
        // if (objectsub->to_string()=="0"){
        //     cout<<"sign"<<objectsub->get_sign();
        // }
        number = object->size - p2;
        if (objectsub->sign == -1)
        {
            // cout<<"here? "<<objecthelp->to_string();

            if (p2 + 1 > g1)
            {
                object = objecthelp;
                break;
            }
            objecthelp->size = p2 + 1;
            objecthelp->capacity = p2 + 1;
            objecthelp->sign = s1;
            int *arphelp = new int[p2 + 1];
            for (int j = 0; j < p2 + 1; j++)
            {
                arphelp[j] = grr1[j];
            }
            objecthelp->unlimited_int = arphelp;
            number -= 1;
            nexttaken = true;
        }
        
        objectsub = sub(objecthelp, i2);
        delete objecthelp;
        // cout<<"find:"<<objectsub->to_string()<<endl;
        int a = 0;
        while (objectsub->sign == 1)
        {
            a += 1;
            UnlimitedInt * temp=new UnlimitedInt;
            temp = sub(objectsub, i2);
            delete objectsub;
            objectsub=temp;
        }
        s += std::to_string(a);
        

        for (int d = 0; d < number; d++)
        {
            s += "0";
        }
        // cout<<"s: "<<s<<endl;
        UnlimitedInt * temp=new UnlimitedInt;
        temp = add(objectsub, i2);
        delete objectsub;
        objectsub=temp;

        int *arobj = objectsub->unlimited_int;
        // cout<<"subb: "<< objectsub->to_string()<<endl;
        int *helper;
        int b = objectsub->size;
        bool c1 = true;
        if (b == 1 and arobj[0] == 0)
        {
            // cout<<"came here";
            b = 0;
        }
        if (nexttaken)
        {
            helper = new int[g1 - p2 - 1 + b];
            int h = 0;
            while (h < b)
            {
                helper[h] = arobj[h];
                h += 1;
            }
            int k = p2 + 1;
            while (h < g1 - p2 - 1 + b)
            {
                helper[h] = grr1[k];
                k += 1;
                h += 1;
            }
        }
        else
        {
            // cout<<"mad";
            helper = new int[g1 - p2 + b];
            int h = 0;
            c1 = false;
            while (h < b)
            {
                helper[h] = arobj[h];
                // cout<<"helgjghvjbkp:"<<helper[h];
                h += 1;
            }
            int k = p2;
            while (h < g1 - p2 + b)
            {
                helper[h] = grr1[k];
                // cout<<"help:"<<helper[h];
                k += 1;
                h += 1;
            }
        }
        object->unlimited_int = helper;
        
        if (c1)
        {
            object->size = g1 - p2 - 1 + b;
        }
        else
        {
            object->size = g1 - p2 + b;
        }
        // cout<<"object: "<< object->size<<endl;
        object->capacity = object->size;
        string sdf=object->to_string();
        delete object;
        object=new UnlimitedInt(sdf);
        UnlimitedInt *stringadd = new UnlimitedInt(s);
        // UnlimitedInt * stringnew=new UnlimitedInt(stringadd->to_string());
        UnlimitedInt * tempp=new UnlimitedInt;
        tempp = add(objectadd, stringadd);
        delete objectadd;
        delete stringadd;
        objectadd=tempp;
        // cout<<"koo: "<< objectadd->to_string()<<endl;
    }
    return objectadd;
}

UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *object1 = div(i1, i2);//-3
    // cout<<"hi"<< object1->to_string()<<endl;
    UnlimitedInt *object2 = mul(i2, object1);//-6
    delete object1;
    UnlimitedInt *object3 = sub(i1, object2);//1
    delete object2;
    return object3;
}

string UnlimitedInt::to_string()
{
    string s = "";
    if (sign < 0)
    {
        s += "-";
    }
    int n = size;
    int y=0;
    // cout<<s[0]<<"hi";
    while(y<n and unlimited_int[y]==0){
        y+=1;
    }
    // cout<<y;
    if (y==n){
        s="0";
        return s;
    }
    for (int j = y; j < n; j++)
    {
        int a = unlimited_int[j];
        s+=std::to_string(a);
    }
    return s;
}

// int main()
// {
//     // cout<<5;
//     // string h="";
//     // for (int j=0;j<6000;j++){
//     //     h+="8";
//     // }
//     // string g="";
//     // for (int j=0;j<2000;j++){
//     //     g+="5";
//     // }
//     UnlimitedInt p(-1413);
//     UnlimitedInt q(14);
//     UnlimitedInt *r = UnlimitedInt::mod(&p, &q);
//     UnlimitedInt *s = UnlimitedInt::add(&p, &q);
// // //     //     // cout<<6;
// //     cout << r->get_size() << endl;
// // //     //     // cout<<5;
// // //     //     int g = r->get_capacity();
// // //     // //     cout << r->get_sign() << endl;
// // //     //     int *arr = r->get_array();
// // //     //     for (int j = 0; j < g; j++)
// // //     //     {
// // //     //         cout << arr[j] << " ";
// // //     //     }
// // //     //     cout << endl;
//     cout << r->to_string() << endl;
//     cout << s->to_string() << endl;
// // //     //     // cout << 5;
// }

