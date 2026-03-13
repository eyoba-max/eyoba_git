package gitPackage;

public class Student {
	String studentName;
	final  String studentID;
	int yearOfStudy;
	double GPA;
	static String universityName;
	static double passingGPA=2.5;
	static final double minGPA=0.0;
	static final double maxGPA=4.0;
	static int totalObject=0;
	Student(String name,String ID,int study,double grade,String uv){
		studentName=name;
		studentID=ID;
		yearOfStudy=study;
		universityName=uv;
		GPA=grade;
		totalObject++;
	}
	void displayStudentInfo() {
		System.out.println(universityName);
		System.out.println(studentName);
		System.out.println(studentID);
		System.out.println(yearOfStudy);
		System.out.println(GPA);
	}
	boolean studentStatus() {
		return GPA>=passingGPA;
	}
	static int getStudentCount() {
		return totalObject;
	}
	
	public static void main(String[] args) {
	final String university="ADDIS ABABA UNIVERSITY";
	Student obj=new Student("MOGES AKLILU","UGR/9316/17",2,3.7,university);
	Student obe=new Student("SENDAFAW GELETE","UGR/6560/17",2,3.8,university);
	obj.displayStudentInfo();
	obe.displayStudentInfo();
	if(obj.studentStatus()) {
		System.out.println(obj.studentName+" is passed");
	}
	else {
		System.out.println(obj.studentName+" is not passed.");
	}
	if(obe.studentStatus()) {
		System.out.println(obe.studentName+" is passed");
	}
	else {
		System.out.println(obe.studentName+" is not passed.");
	}
	int count=getStudentCount();
	System.out.println("Total number of Student object created is: "+count);
}
}

