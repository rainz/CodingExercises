package org.rainz;

public class Triangle {
	private String type;
	private int height;
	
	private Point pointA;
	private Point pointB;
	private Point pointC;
	
	public Point getPointA() {
		return pointA;
	}

	public void setPointA(Point pointA) {
		this.pointA = pointA;
	}

	public Point getPointB() {
		return pointB;
	}

	public void setPointB(Point pointB) {
		this.pointB = pointB;
	}

	public Point getPointC() {
		return pointC;
	}

	public void setPointC(Point pointC) {
		this.pointC = pointC;
	}

	
	public int getHeight() {
		return height;
	}

	public Triangle() {
		
	}
	
	public Triangle(String type) {
		this.type = type;
	}

	public Triangle(int height) {
		this.height = height;
	}
	
	public Triangle(String type, int height) {
		this.type = type;
		this.height = height;
	}
	
	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}

	public void draw() {
		//System.out.println(getType() + " is drawn of height " + getHeight());
		System.out.println("Point A=("+getPointA().getX()+", "+getPointA().getY()+")");
		System.out.println("Point B=("+getPointB().getX()+", "+getPointB().getY()+")");
		System.out.println("Point C=("+getPointC().getX()+", "+getPointC().getY()+")");
	}
}
