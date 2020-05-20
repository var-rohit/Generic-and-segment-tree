import java.util.*;

class TreeNode<Integer>
{
	int data;
	ArrayList<TreeNode<Integer>> children;

	TreeNode(int data)
	{
		this.data = data;
		children = new ArrayList<>();
	}
}


public class generic
{
	public static TreeNode<Integer> takeInput()
	{
		Scanner s = new Scanner(System.in);
		System.out.println("Enter node");
		int n = s.nextInt();
		TreeNode<Integer> root = new TreeNode<Integer>(n);
		System.out.println("Enter number of children for node with data "+n);
		int childCount = s.nextInt();
		for(int i=0;i<childCount;i++)
		{
			TreeNode<Integer> child = takeInput();
			root.children.add(child);
		}

		return root;

	}

	public static void print(TreeNode<Integer> root)
	{
		String str = root.data + ": ";

		for(int i=0;i<root.children.size();i++)
		{
			str  = str + root.children.get(i).data+",";
		}

		System.out.println(str);
		for(int i=0;i<root.children.size();i++)
			{
				print(root.children.get(i));
			}
	}

	static TreeNode<Integer> takeInputLevelWise()
	{
		Scanner s = new Scanner(System.in);
		Queue<TreeNode<Integer>> q = new LinkedList<>();
		System.out.println("Enter node");
		int data = s.nextInt();
		TreeNode<Integer> root = new TreeNode<>(data);

		q.add(root);
		while(q.size()>0)
		{
			int n = q.size();
			while(n>0)
			{
				TreeNode<Integer> node = q.poll();

				System.out.println("Enter number of children of "+node.data);
				int childCount = s.nextInt();
				for(int i=0;i<childCount;i++)
				{
					System.out.println("Enter "+(i+1)+" th child");
					int child = s.nextInt();
					TreeNode<Integer> value = new TreeNode<Integer>(child);
					node.children.add(value);
					q.add(value);
				}

				n--;
			}
		}

		return root;


	}



	public static void main(String[] args) {

		TreeNode<Integer> root = takeInputLevelWise();
		print(root);

	}
}
