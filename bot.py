from config import keys
from selenium import webdriver
from bs4 import BeautifulSoup
import time

def order(k):
    driver = webdriver.Chrome('./chromedriver')
    driver.get(k['url'])
    #first button
    driver.find_element_by_xpath('//*[@id="sign-in"]/a').click()
    #login username
    driver.find_element_by_xpath('//*[@id="username"]').send_keys(k['netID'])
    #login password
    driver.find_element_by_xpath('//*[@id="password"]').send_keys(k['pass'])
    #login button
    driver.find_element_by_xpath('//*[@id="loginform"]/div[4]/button').click()
    driver.implicitly_wait(30)
    i = 1
    numCourses = 4
    f = open("input.txt", "w")
    while i <= int(numCourses):
        #choose course
        driver.find_element_by_xpath('//*[@id="_27_1termCourses_noterm"]/ul/li['+str(i)+']/a').click()
        driver.implicitly_wait(30)
        #finding tools
        tools = driver.find_element_by_xpath("//span[@title='Tools']")
        t_link = tools.find_element_by_xpath('..') #parent
        t_link.click()
        driver.implicitly_wait(30)
        #my grades
        driver.find_element_by_xpath("//a[contains(text(), 'My Grades')]").click()
        driver.implicitly_wait(30)
        html = driver.page_source
        soup = BeautifulSoup(html, 'lxml')


        # DFS for all divs
        results = soup.find('div', attrs = {'id': 'globalNavPageContentArea'})
        stack = []
        stack.append(results)
        visited = []
        grades = []
        #while the stack is not empty
        while(len(stack) > 0):
            results = stack[len(stack)-1]
            if(not(results in visited)):
                visited.append(results)
            more = 0
            #if there are more ones
            if(len(results.find_all('div')) > 0):
                for div in results.find_all('div'):
                    if(not (div in visited)):
                        stack.append(div)
                        more = 1
                        break
            if(more == 0):
                stack.pop()
    
        for ele in visited:
            if (ele.has_attr('class')):
                if(set(ele.attrs['class']) == set(['cell','gradable'])):
                    for a in ele.find_all('a'):
                        f.write("\n")
                        f.write(a.text)
            if (ele.has_attr('class')):
                if(set(ele.attrs['class']) == set(['cell','grade'])):
                    for span in ele.find_all('span'):
                        f.write("\n")
                        f.write(span.text)
                        
        #go back to home
        driver.find_element_by_xpath('//*[@id="Home"]/a').click()
        driver.implicitly_wait(30)
        i = i + 1
    
    
    f.close()
    driver.close()
    
if __name__ == '__main__':
    order(keys)
