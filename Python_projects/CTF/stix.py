from collections import defaultdict

def analyze_german_text(text):
    # Немецкий алфавит (включая умлауты и ß)
    german_alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZÄÖÜß'
    
    # Приводим текст к верхнему регистру
    text_upper = text.upper()
    total_letters = sum(1 for char in text_upper if char in german_alphabet)
    
    # Подсчет букв
    counts = defaultdict(int)
    for char in text_upper:
        if char in german_alphabet:
            counts[char] += 1
    
    # Сортировка по частоте (по убыванию)
    sorted_counts = sorted(counts.items(), key=lambda x: (-x[1], x[0]))
    
    # Вывод в табличном формате
    print("| буква | употреблений | частотность |")
    print("|---|---|---|")
    for letter, count in sorted_counts:
        frequency = count / total_letters
        print(f"| {letter.lower()} | {count} | {frequency:.8f} | {frequency:.2%} |")
    
    # Возвращаем результаты для возможного дальнейшего анализа
    return {
        'total_letters': total_letters,
        'letter_counts': dict(sorted_counts)
    }

# Ваш текст
text = '''Cz uwy Vtyedü Jleemd, cfueäyi Jidtüuzuwsdx, Vatvovt ues Uößsßbl! Jld ßtoihopn viöeääqfpwüä, Äzöfüiigäe, Önhx Ksyzbxvöv. Dümge Litohd ßwgühg hiühyr, Iir pls Bbxv uoäeck aednhvv, Oäzy Chgbcxig wpycqp Phkxvt, Sx Dümg slueehd Üzpxhe heyöo.

    Spqc föetvempapn, Bmelßümqp! Rytmvp Deß uil gluyqp Lüzo! Stpöeh, yveät Rehdctgrhed Mlv yiw ßhqesh Mulhl hoxqyn!

    Inl phd wfhkh Serv kyleufqp, Syäyj Ilpuchys Qydfpr qj mvlg, Ieh ibn sükphe Ötbt hläuckyn, Üqröks itbdhg Sußie eßu! Im, zsh pöuk ger ümge Bndvh Eüwg dhgwt rxz dpt Dbgscfödg! Pwd oil’s wqd shwdägl, gyä skiälp Fdtpscß mzfä lui hbebnl Owzu!

    Nuj gyw ghrnew Xhxj pümhypyd, Hlöxirn cqt Epajsväße! Rx xew Yßqtzüä evlopt imy, Wx mdb Wzßtdspgde kllownß.

    Rtslßy ltbwküq ulün Vqusc Pg ühg Nrmüoew mdb Pokjl; Soep Glwyn, lßkq Eäitg Vqerec märpy Qyuscgjmt. Dfsii aan zhq wzi jgü Synec, Ibnpu Ebhhcß, avslffk mf Txm; Vyoxlgo öclö düp Suät fqjsßtg, Npx öeh Gäeäbä cvsxi qet Axtk.

    Mär bäubbg cwyühl, Üiäöbownm? Mkzügo üw xpn Igäözodb, Asäi? Mmfä’ ßhc yveät Rehdctgrhed! Üßil Sdnqxhz bjn vt rxhcig.

    Fäntph uüwnl gbp skdlkp Odphd Xä xvt yhiwig Nlätb. Idüjxv, Ilpuui orpqäe güü Füühl Sn uil Gäüsqp Lüzovpösr. Söömpu kyfwk gbv cöb düq Deßtdx, Tacäyd cöb düp Yiätzwhzk, Gjydlpn hreld zhq lz utg Idövec, Hbe önr Chuüfm Iqää nygät unmxv.

    Shbä, öly beyqy Sxumqp ßäwyxhg Öuhgä dpz Gtöyüzm gtüohk’kyn Yßzx, Ooluyl, Elfdüu, yuän Ämkz, Üfymgbr, wyi yiw Pdvg nla Mzhapn.

    Rxm dpy Vmkdxtbl Iyeehüjipödv Oötvybv mße uig Fxyröksh pg. Sw xpr Lxaewm rehüätf Xxapl Äibtpä rth rüg Wmoxpri Fuhw. Itr gsi Ueswvpni Uhnwnmohdwt Mzhäd mrq bhän Emkzüä rvkg, Öuhgä dpu Qtü tügjihgrtüu Määöd Cls ya Vyql öeh Iggpß rehuc.

    Söbgyd mlwbg, Üqkvlactg! Uweöek jpr öqd ohfht Svoo! Ördfyn fkdbö Ektldbyüt Ömld pqm stajtl Wqod büöhhwnm.

    Srgktld nuwn bdg nßlge yshüybvyw; Stlin ßzß’c, luctg xoyßcx cö spqm. Stob jgü Clvuk ühlü zhök yüzxvp, Fßt uig Fäügqp eysä vtzäelq. Arxßk fpr Hpwyh mpi nilgpzrqp, Icgyiö Öxdvibnö zdt yshöbvkg, Teyqy Täjmqp edze zkg zrüümew, Sdtps Htöv pure ylg.

    Uwzdb Tqxjeüeöoh iib vpymtfukto! Swmreisänd mhq jocöy Phed! Bhyxeä, cäqty Iiyipywzüöo Rßlgehg Vbol, zbp wyu aeäqbßvsk.

    Tlvwxp sfuödpßß tp Bdyubhg, Sn uil Täitoh tdzxdhf Nllw Örßujqp Eräzlööd Krqginikqp, Ryt Rvttheyjeuwö Gqorüäfmv— Üäüuil, füqdsv jdä ymtyw Sywtew, Fdxp rüf qeoep Repyr uydtug, Äpnl gyw Stluuv htw Kübayb ujäikcyn: Öqdche Vzuj gyv glwyn Rnhcv.

    Rüä xvt Mdehqy Wßyäqo xdryd, Gyw düü Meäiößu Tpagv slpiiw, Wipzdc Jxrg xvö aetüq Aeßzß Hesha Mlhlweccyld mnbv aßtg!

    Vhmdec Pöt ßu rökküfyc Oyßdüq, Äiüod, iq ryt Pduwsuäh reßuß, Qzüwyyzv apstlroäudx Hüutg, Pcäähümo gpödx Idüjgü wgö Fümgd, Üjmxhdiihbb qxr Asgirzßßtactg, — Stpöeh, küld’ nr Swg läx Soöd— Düp Reämhqpekt mvlgp Khrgew, Cmehdwpgx gyä Lmkynnyte!

    Tqxzbvüo öec lyiü’ödx Cühyyb gbohkil, Sopvztg ßtb ülybeb khlöudx Asyä: Wvö Aplmfxe dydf bh itbd, Twsweuo eb kdt gsb Govtgpnhmwhdnq!

    Bhgkjgx yhw Tpuunwnmühgktg, Wthcmlw uuop cqö Pegyölwst, Wrzfwbms chv ßyd Toprßivedädx, Jzrßy swz öeb Lhcsödblqxi! Tmfä öiü Whtpu ryoxüä eveyw! Bhyxeä, äqtpwk jgü uoßmbio eßu, Yvosc Gpdgyän irel gnqshpüä, Pdg xße Wselp uhökg btäi uyßn.

    Umge snhets Rrmukbpdiüouwmd! Cxfüä Mukelf yp Eeßlgqpglsä! Stpöeh, ibnpu rmpßktg Jslecx Dös önr Fqgüälzfädehü Fuwm.

    lthytiz_olapnüuy_oön_ßy_map'''  # Вставьте весь текст здесь

# Анализируем текст
results = analyze_german_text(text)

# Дополнительная информация
print(f"\nВсего букв: {results['total_letters']}")
missing = [c for c in 'ABCDEFGHIJKLMNOPQRSTUVWXYZÄÖÜß' if c not in results['letter_counts']]
print(f"Отсутствующие буквы: {', '.join(missing)}")