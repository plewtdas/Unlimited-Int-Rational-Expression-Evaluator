/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
// #include "ulimitedint.cpp"
// #include <iostream>

UnlimitedRational::UnlimitedRational() {
    p=nullptr;
    q=nullptr;
}

UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{
    p = num;
    q = den;
    // UnlimitedInt *object1 = p;
    // UnlimitedInt *object2 = q;
    // UnlimitedInt *object4 ;
    // int *arr2 = object2->get_array();
    // int b = object2->get_size();
    int cny=0;

    int ba=p->get_size();
    int * arra=new int[ba];
    int * get=p->get_array();
    for (int j=0;j<ba;j++){
        arra[j]=get[j];
    }
    UnlimitedInt *object1 = new UnlimitedInt(arra,ba,p->get_sign(),ba) ;

    int b=q->get_size();
    int * arr2=new int[b];
    int * getq=q->get_array();
    for (int j=0;j<b;j++){
        arr2[j]=getq[j];
    }
    UnlimitedInt *object2 = new UnlimitedInt(arr2,b,q->get_sign(),b) ;


    while (b != 1 or arr2[0] != 0)
    {  
        // if (cny>=1){
        //     delete object4;
        //     object4=nullptr;
        // }
        // object4=object1;
        UnlimitedInt *object3 = object2;
        
        // cout<<"object1: "<< object1->to_string()<<endl;
        // cout<<"object2: "<< object2->to_string()<<endl;

        object2 = UnlimitedInt::mod(object1, object2);
        
        // cout<<"object1 after mod: "<< object1->to_string()<<endl;
        // cout<<"object2 after mod: "<< object2->to_string()<<endl;

        // UnlimitedInt *temp ;
        // temp=UnlimitedInt::mod(object1, object2);
        // UnlimitedInt * object4=object1;
        // if (object1->!=p){
        delete object1;
        // object1=nullptr;
        // UnlimitedInt *object1 = object3;
        // object1=nullptr;
        object1 = object3;
        // cout<<object1->to_string()<<endl;
        
        b = object2->get_size();
        arr2 = object2->get_array();
        // cout<<arr2[0];
        // cout<<b;
        cny+=1;
    }
    delete object2;
    // cout<<"cool: "<<object1->to_string()<<endl;
    
    // cout<<"jl";
    // object 1 is now my hcf
    // cout<<"kl";
    // cout<<p->to_string()<<" " <<q->to_string()<<endl;
    UnlimitedInt *object5 = UnlimitedInt::div(p, object1);
    UnlimitedInt *object6 = UnlimitedInt::div(q, object1);
    
    p=object5;
    q=object6;
    
}

UnlimitedRational::~UnlimitedRational() {
    delete p;
    delete q;

}

UnlimitedInt *UnlimitedRational::get_p()
{
    return p;
}

UnlimitedInt *UnlimitedRational::get_q()
{
    return q;
}

string UnlimitedRational::get_p_str()
{
    return p->to_string();
}

string UnlimitedRational::get_q_str()
{
    return q->to_string();
}

string UnlimitedRational::get_frac_str()
{

    string s1 = p->to_string();
    string s2 = q->to_string();

    string s3 = s1 + "/" + s2;
    return s3;
}

UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *p1 = i1->get_p();
    UnlimitedInt *q1 = i1->get_q();
    UnlimitedInt *p2 = i2->get_p();
    UnlimitedInt *q2 = i2->get_q();

    string ss1 = q1->to_string();
    string ss2 = q2->to_string();

    UnlimitedRational *object = new UnlimitedRational;
    if (ss1.length() == 1 and ss1[0] == '0')
    {
        UnlimitedInt *object0 = new UnlimitedInt(0);
        UnlimitedInt *object1 = new UnlimitedInt(0);
        object->p = object0;
        object->q = object1;
        return object;
    }
    if (ss2.length() == 1 and ss2[0] == '0')
    {
        UnlimitedInt *object0 = new UnlimitedInt(0);
        UnlimitedInt *object01 = new UnlimitedInt(0);
        object->p = object0;
        object->q = object01;
        return object;
    }

    UnlimitedInt *mult1 = UnlimitedInt::mul(p1, q2);
    UnlimitedInt *mult2 = UnlimitedInt::mul(p2, q1);
    UnlimitedInt *mult3 = UnlimitedInt::mul(q2, q1);
    UnlimitedInt *add1 = UnlimitedInt::add(mult1, mult2);
    // cout<<mult3->to_string()<<" hi";
    int ba=add1->get_size();
    int * arra=new int[ba];
    int * get=add1->get_array();
    for (int j=0;j<ba;j++){
        arra[j]=get[j];
    }
    UnlimitedInt *object1 = new UnlimitedInt(arra,ba,add1->get_sign(),ba) ;

    int b=mult3->get_size();
    int * arr2=new int[b];
    int * getq=mult3->get_array();
    for (int j=0;j<b;j++){
        arr2[j]=getq[j];
    }
    UnlimitedInt *object2 = new UnlimitedInt(arr2,b,mult3->get_sign(),b) ;
    
    delete mult1;
    delete mult2;
    // UnlimitedInt *object2 = mult3;
    // int *arr2 = object2->get_array();
    // int b = object2->get_size();
    
    while (b != 1 or arr2[0] != 0)
    {
        UnlimitedInt *object3 = object2;
        // UnlimitedInt *temp=object2 ;
        // temp=UnlimitedInt::mod(object1, object2);
        // delete object2;
        // temp=object2;
        object2= UnlimitedInt::mod(object1, object2);
        // cout<<object2->to_string()<<"modwali";
        // delete object3;
        // if (object1!=add1){
        delete object1;
        object1 = object3;
        // delete object3;
        b = object2->get_size();
        arr2 = object2->get_array();

    }
    delete object2;
    // object 1 is now my hcf
    // cout<<object1->to_string()<<" bye";
    UnlimitedInt *object5 = UnlimitedInt::div(add1, object1);
    UnlimitedInt *object6 = UnlimitedInt::div(mult3, object1);
    delete add1;
    delete object1;
    delete mult3;

    string s3 = object6->to_string();
    if (s3.length() == 1 and s3[0] == '0')
    {
        delete object5;
        delete object6;
        UnlimitedInt *object0 = new UnlimitedInt(0);
        UnlimitedInt *object01 = new UnlimitedInt(0);
        object->p = object0;
        object->q = object01;
        return object;
    }
    object->p = object5;
    object->q = object6;
    return object;
}

UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *p1 = i1->get_p();
    UnlimitedInt *q1 = i1->get_q();
    UnlimitedInt *p2 = i2->get_p();
    UnlimitedInt *q2 = i2->get_q();

    string ss1 = q1->to_string();
    string ss2 = q2->to_string();

    UnlimitedRational *object = new UnlimitedRational;
    if (ss1.length() == 1 and ss1[0] == '0')
    {
        UnlimitedInt *object0 = new UnlimitedInt(0);
        UnlimitedInt *object01 = new UnlimitedInt(0);
        object->p = object0;
        object->q = object01;
        return object;
    }
    if (ss2.length() == 1 and ss2[0] == '0')
    {
        UnlimitedInt *object0 = new UnlimitedInt(0);
        UnlimitedInt *object01 = new UnlimitedInt(0);
        object->p = object0;
        object->q = object01;
        return object;
    }

    UnlimitedInt *mult1 = UnlimitedInt::mul(p1, p2);
    // UnlimitedInt* mult2=UnlimitedInt::mul(p2,q1);
    UnlimitedInt *mult3 = UnlimitedInt::mul(q2, q1);
    // UnlimitedInt* add1=UnlimitedInt::add(mult1,mult2);
    // UnlimitedRational* object=new UnlimitedRational;

    int ba=mult1->get_size();
    int * arra=new int[ba];
    int * get=mult1->get_array();
    for (int j=0;j<ba;j++){
        arra[j]=get[j];
    }
    UnlimitedInt *object1 = new UnlimitedInt(arra,ba,mult1->get_sign(),ba) ;

    int b=mult3->get_size();
    int * arr2=new int[b];
    int * getq=mult3->get_array();
    for (int j=0;j<b;j++){
        arr2[j]=getq[j];
    }
    UnlimitedInt *object2 = new UnlimitedInt(arr2,b,mult3->get_sign(),b);


    // UnlimitedInt *object1 = mult1;
    // UnlimitedInt *object2 = mult3;
    // int *arr2 = object2->get_array();
    // int b = object2->get_size();
    int cny=0;
    while (b != 1 or arr2[0] != 0)
    {
        UnlimitedInt *object3 = object2;
        object2 = UnlimitedInt::mod(object1, object2);
        // if (cny>=1){
        delete object1;
        object1 = object3;
        b = object2->get_size();
        arr2 = object2->get_array();
        cny++;
    }
    delete object2;
    // object 1 is now my hcf
    UnlimitedInt *object5 = UnlimitedInt::div(mult1, object1);
    UnlimitedInt *object6 = UnlimitedInt::div(mult3, object1);
    delete mult1;
    delete mult3;
    delete object1;

    string s3 = object6->to_string();
    if (s3.length() == 1 and s3[0] == '0')
    {
        delete object5;
        delete object6;
        UnlimitedInt *object0 = new UnlimitedInt(0);
        UnlimitedInt *object1 = new UnlimitedInt(0);
        object->p = object0;
        object->q = object1;
        return object;
    }

    object->p = object5;
    object->q = object6;
    return object;
}

UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *p1 = i1->get_p();
    UnlimitedInt *q1 = i1->get_q();
    UnlimitedInt *p2 = i2->get_p();
    UnlimitedInt *q2 = i2->get_q();

    string ss1 = q1->to_string();
    string ss2 = q2->to_string();

    UnlimitedRational *object = new UnlimitedRational;
    if (ss1.length() == 1 and ss1[0] == '0')
    {
        UnlimitedInt *object0 = new UnlimitedInt(0);
        UnlimitedInt *object01 = new UnlimitedInt(0);
        object->p = object0;
        object->q = object01;
        return object;
    }
    if (ss2.length() == 1 and ss2[0] == '0')
    {
        UnlimitedInt *object0 = new UnlimitedInt(0);
        UnlimitedInt *object1 = new UnlimitedInt(0);
        object->p = object0;
        object->q = object1;
        return object;
    }

    UnlimitedInt *mult1 = UnlimitedInt::mul(p1, q2);
    UnlimitedInt *mult2 = UnlimitedInt::mul(p2, q1);
    UnlimitedInt *mult3 = UnlimitedInt::mul(q2, q1);
    UnlimitedInt *add1 = UnlimitedInt::sub(mult1, mult2);
    // UnlimitedRational* object=new UnlimitedRational;


    int ba=add1->get_size();
    int * arra=new int[ba];
    int * get=add1->get_array();
    for (int j=0;j<ba;j++){
        arra[j]=get[j];
    }
    UnlimitedInt *object1 = new UnlimitedInt(arra,ba,add1->get_sign(),ba) ;

    int b=mult3->get_size();
    int * arr2=new int[b];
    int * getq=mult3->get_array();
    for (int j=0;j<b;j++){
        arr2[j]=getq[j];
    }
    UnlimitedInt *object2 = new UnlimitedInt(arr2,b,mult3->get_sign(),b);

    delete mult1;
    delete mult2;

    // UnlimitedInt *object1 = add1;
    // UnlimitedInt *object2 = mult3;
    // int *arr2 = object2->get_array();
    // int b = object2->get_size();
    int cny=0;
    while (b != 1 or arr2[0] != 0)
    {
        UnlimitedInt *object3 = object2;
        object2 = UnlimitedInt::mod(object1, object2);
        // if (cny>=1){
        delete object1;
        object1 = object3;
        cny++;
        b = object2->get_size();
        arr2 = object2->get_array();
    }
    delete object2;
    // object 1 is now my hcf
    UnlimitedInt *object5 = UnlimitedInt::div(add1, object1);
    UnlimitedInt *object6 = UnlimitedInt::div(mult3, object1);
    delete add1;
    delete object1;
    delete mult3;

    string s3 = object6->to_string();
    if (s3.length() == 1 and s3[0] == '0')
    {
        delete object5;
        delete object6;
        UnlimitedInt *object0 = new UnlimitedInt(0);
        UnlimitedInt *object1 = new UnlimitedInt(0);
        object->p = object0;
        object->q = object1;
        return object;
    }

    object->p = object5;
    object->q = object6;
    return object;
}

UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *p1 = i1->get_p();
    UnlimitedInt *q1 = i1->get_q();
    UnlimitedInt *p2 = i2->get_p();
    UnlimitedInt *q2 = i2->get_q();

    string ss1 = q1->to_string();
    string ss2 = q2->to_string();

    UnlimitedRational *object = new UnlimitedRational;
    if (ss1.length() == 1 and ss1[0] == '0')
    {
        
        UnlimitedInt *object0 = new UnlimitedInt(0);
        UnlimitedInt *object1 = new UnlimitedInt(0);
        object->p = object0;
        object->q = object1;
        return object;
    }
    if (ss2.length() == 1 and ss2[0] == '0')
    {
        UnlimitedInt *object0 = new UnlimitedInt(0);
        UnlimitedInt *object1 = new UnlimitedInt(0);
        object->p = object0;
        object->q = object1;
        return object;
    }

    UnlimitedInt *mult1 = UnlimitedInt::mul(p1, q2);
    
    // UnlimitedInt* mult2=UnlimitedInt::mul(p2,q1);
    UnlimitedInt *mult3 = UnlimitedInt::mul(q1, p2);
    
    
    // UnlimitedInt* add1=UnlimitedInt::add(mult1,mult2);
    // UnlimitedRational* object=new UnlimitedRational;


    int ba=mult1->get_size();
    int * arra=new int[ba];
    int * get=mult1->get_array();
    for (int j=0;j<ba;j++){
        arra[j]=get[j];
    }
    UnlimitedInt *object1 = new UnlimitedInt(arra,ba,mult1->get_sign(),ba) ;

    int b=mult3->get_size();
    int * arr2=new int[b];
    int * getq=mult3->get_array();
    for (int j=0;j<b;j++){
        arr2[j]=getq[j];
    }
    UnlimitedInt *object2 = new UnlimitedInt(arr2,b,mult3->get_sign(),b);

    // UnlimitedInt *object1 = mult1;
    // UnlimitedInt *object2 = mult3;
    // int *arr2 = object2->get_array();
    // int b = object2->get_size();
    int cny=0;
    while (b != 1 or arr2[0] != 0)
    {
        // cout<<"???";
        UnlimitedInt *object3 = object2;
        object2 = UnlimitedInt::mod(object1, object2);
        // if (cny>=1){
        delete object1;
        object1 = object3;
        b = object2->get_size();
        arr2 = object2->get_array();
        cny++;
    }
    delete object2;
    // object 1 is now my hcf
    // cout<<"jonkn"<<endl;
    // cout<<object1->to_string()<<endl;
    // cout<<"mult3: "<< mult3->to_string()<<endl;
    // cout<<mult1->to_string()<<endl;
    UnlimitedInt *object5 = UnlimitedInt::div(mult1, object1);
    // cout<< object1->to_string()<<endl;
    // cout<<object5->to_string()<<endl;
    UnlimitedInt *object6 = UnlimitedInt::div(mult3, object1);
    // cout<<"goy:";
    // cout<<object6->to_string()<<endl;
    delete mult1;
    delete mult3;
    delete object1;
    string s3 = object6->to_string();
    if (s3.length() == 1 and s3[0] == '0')
    {
        // cout<<"ha";
        delete object5;
        delete object6;

        UnlimitedInt *object0 = new UnlimitedInt(0);
        UnlimitedInt *object1 = new UnlimitedInt(0);
        object->p = object0;
        object->q = object1;
        return object;
    }

    object->p = object5;
    
    object->q = object6;
    // cout<<object6->to_string();
    return object;
}

// int main(){
//     // cout<<6;
//     UnlimitedInt w("2");
//     UnlimitedInt e("51");
//     // UnlimitedInt t("51");
//     // UnlimitedInt y("1");
//     UnlimitedInt g("13");
//     UnlimitedInt h("1");
//     UnlimitedRational r(&w,&e);
// //     UnlimitedRational d(&t,&y);
//     UnlimitedRational v(&g,&h);
// //     UnlimitedRational *u= UnlimitedRational::div(&r,&d);
//     UnlimitedRational *p= UnlimitedRational::add(&r,&v);
//     cout<<p->get_frac_str()<<endl;
// // //     // cout<<d.get_frac_str();
//     // cout<<r.get_p_str()<<endl;
//     // cout<<r.get_q_str()<<endl;
//     cout<<r.get_frac_str();
// // //     // cout<<"over";
// //    return 0;
// }

// int main() {
//      UnlimitedInt *num1= new UnlimitedInt(2);
//      UnlimitedInt *den1= new UnlimitedInt(1);
//     UnlimitedInt* den2 = new UnlimitedInt("8");
//     UnlimitedInt* num2 = new UnlimitedInt("4");
//     UnlimitedRational* rat1 = new UnlimitedRational(num1, den1);  
//     UnlimitedRational* rat2 = new UnlimitedRational(num2, den2);
//     UnlimitedRational* sum = UnlimitedRational::add(rat1, rat2);
//     // cout<<h->to_string()<<endl;
//     // cout<<"addends"<<endl;
//     UnlimitedRational* difference = UnlimitedRational::sub(rat1, rat2);
//     UnlimitedRational* product = UnlimitedRational::mul(rat1, rat2);
//     UnlimitedRational* quotient = UnlimitedRational::div(rat1, rat2);
//     // Display the resultss
//     std::cout << "Rational 1: " << rat1->get_frac_str() << std::endl;
    
//     std::cout << "Rational 2: " << rat2->get_frac_str() << std::endl;
//     std::cout << "Sum: " << sum->get_frac_str() << std::endl;

//     std::cout << "Difference: " << difference->get_frac_str() << std::endl;

//     std::cout << "Product: " << product->get_frac_str() << std::endl;
//     std::cout << "Quotient: " << quotient->get_frac_str() << std::endl;

//     delete num1;
//     delete den1;
//     delete num2;
//     delete den2;
//     delete rat1;
//     delete rat2;
//     return 0;
// }
