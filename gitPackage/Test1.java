package gitPackage;

public class Test1 {
	int age;
	String name;
	final String ID;
	Test1(String id, String name, int age){
		ID=id;
		System.out.println("your name is "+name+" you are "+age+" years old");
		System.out.println("your identification number is "+ID);
	}
}
