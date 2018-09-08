/**   
 * Copyright © 2018 liao. All rights reserved.
 * 
 *	Life is but a span
 * @Package: TSP 
 * @author: Administrator   
 * @date: 2018年9月7日 下午2:53:31 
 */
package TSP;

/**
 * @date: 2018年9月7日 下午2:53:31
 * @episode : 
 * 种群类
 * 包含：
 *         1.add 添加物种
 *         2.traverse 遍历
 */
public class SpeciesPopulation {
	Specieslndividual head;//头结点
    int speciesNum;//物种数量

    public SpeciesPopulation()
    {
        head=new Specieslndividual();
        speciesNum=TSPData.SPECIEN_NUM;
    }

    //添加物种
    void add(Specieslndividual species)
    {
        Specieslndividual point=head;//游标
        while(point.next != null)//寻找表尾结点
            point=point.next;
        point.next=species;
    }

    //遍历
    void traverse()
    {
        Specieslndividual point=head.next;//游标
        while(point != null)//寻找表尾结点
        {
            for(int i=0;i<TSPData.CITY_NUM;i++)
                System.out.print(point.genes[i]+" ");
            System.out.println(point.distance);
            point=point.next;
        }
        System.out.println("_______________________");
    }

}
